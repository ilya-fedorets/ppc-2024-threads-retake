// Copyright 2024 Fedorets Ilia

#include "seq/fedorets_i_simpson/include/simpson.hpp"

#include <thread>

using namespace std::chrono_literals;

double fedorets_i_simpson_seq::getSimpson(std::function<double(std::vector<double>)>* f,
                                          std::vector<std::pair<double, double>>* limits, std::vector<int>* n) {
  int dim = (*n).size();
  std::vector<double> h(dim);
  int64_t counter = 1;
  for (int i = 0; i < dim; ++i) {
    h[i] = ((*limits)[i].second - (*limits)[i].first) / (*n)[i];
    counter *= (*n)[i];
  }
  double result = 0.0;
  for (int i = 0; i < counter; ++i) {
    std::vector<std::vector<double>> params(dim);
    int temp = i;
    for (int j = 0; j < dim; ++j) {
      params[j].push_back((*limits)[j].first + temp % (*n)[j] * h[j]);
      params[j].push_back((*limits)[j].first + temp % (*n)[j] * h[j] + h[j] / 2);
      params[j].push_back((*limits)[j].first + temp % (*n)[j] * h[j] + h[j] / 2);
      params[j].push_back((*limits)[j].first + temp % (*n)[j] * h[j] + h[j] / 2);
      params[j].push_back((*limits)[j].first + temp % (*n)[j] * h[j] + h[j] / 2);
      params[j].push_back((*limits)[j].first + temp % (*n)[j] * h[j] + h[j]);
      temp /= (*n)[j];
    }
    std::vector<double> point;
    for (int ii = 0; ii < pow(6, dim); ++ii) {
      int temp = ii;
      for (int j = 0; j < dim; ++j) {
        point.push_back(params[j][temp % 6]);
        temp /= 6;
      }
      result += (*f)(point);
      point.clear();
    }
    params.clear();
  }
  for (int i = 0; i < dim; ++i) {
    result *= h[i] / 6.0;
  }
  return result;
}

bool fedorets_i_simpson_seq::SimpsonSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  // input_ = reinterpret_cast<int*>(taskData->inputs[0])[0];
  f = reinterpret_cast<std::function<double(std::vector<double>)>*>(taskData->inputs[0]);
  limits = reinterpret_cast<std::vector<std::pair<double, double>>*>(taskData->inputs[1]);
  n = reinterpret_cast<std::vector<int>*>(taskData->inputs[2]);

  res = 0;
  return true;
}

bool fedorets_i_simpson_seq::SimpsonSequential::validation() {
  internal_order_test();
  // Check count elements of output
  // return taskData->inputs_count[0] == 1 && taskData->outputs_count[0] == 1;
  return taskData->inputs_count.size() == 3 && taskData->outputs_count.size() == 1;
}

bool fedorets_i_simpson_seq::SimpsonSequential::run() {
  internal_order_test();
  res = getSimpson(f, limits, n);
  return true;
}

bool fedorets_i_simpson_seq::SimpsonSequential::post_processing() {
  internal_order_test();
  reinterpret_cast<double*>(taskData->outputs[0])[0] = res;
  return true;
}
