// Copyright 2024 Fedorets Ilia

#include <gtest/gtest.h>

#include <vector>

#include "seq/fedorets_i_simpson/include/simpson.hpp"

TEST(fedorets_i_simpson_seq, Func_1) {
  // Create data
  std::vector<double> out(1, 0);

  const std::function<double(std::vector<double>)> f = [](std::vector<double> vec) {
    double x = vec[0];
    double y = vec[1];
    return x * x - 2 * y;
  };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}});
  std::vector<int> n({3, 3});

  auto funcPtr = std::make_unique<std::function<double(std::vector<double>)>>(f);
  auto limPtr = std::make_unique<std::vector<std::pair<double, double>>>(limits);
  auto nPtr = std::make_unique<std::vector<int>>(n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_seq::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  taskSequential.run();
  taskSequential.post_processing();
  ASSERT_NEAR(294, out[0], 0.1);

  delete reinterpret_cast<std::function<double(std::vector<double>)> *>(taskDataSeq->inputs[0]);
  delete reinterpret_cast<std::vector<std::pair<double, double>> *>(taskDataSeq->inputs[1]);
  delete reinterpret_cast<std::vector<int> *>(taskDataSeq->inputs[2]);
}

TEST(fedorets_i_simpson_seq, Func_2) {
  // Create data
  std::vector<double> out(1, 0);

  const std::function<double(std::vector<double>)> f = [](std::vector<double> vec) {
    double x = vec[0];
    double y = vec[1];
    double z = vec[2];
    return log10(2 * x * x) + sqrt(z) + 5 * y;
  };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {2, 5}});
  std::vector<int> n({2, 2, 2});

  auto funcPtr = std::make_unique<std::function<double(std::vector<double>)>>(f);
  auto limPtr = std::make_unique<std::vector<std::pair<double, double>>>(limits);
  auto nPtr = std::make_unique<std::vector<int>>(n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_seq::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  taskSequential.run();
  taskSequential.post_processing();
  ASSERT_NEAR(203.7, out[0], 0.1);

  delete reinterpret_cast<std::function<double(std::vector<double>)> *>(taskDataSeq->inputs[0]);
  delete reinterpret_cast<std::vector<std::pair<double, double>> *>(taskDataSeq->inputs[1]);
  delete reinterpret_cast<std::vector<int> *>(taskDataSeq->inputs[2]);
}

TEST(fedorets_i_simpson_seq, Func_3) {
  // Create data
  std::vector<double> out(1, 0);

  const std::function<double(std::vector<double>)> f = [](std::vector<double> vec) {
    double x = vec[0];
    double y = vec[1];
    double z = vec[2];
    return x * y * z;
  };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {4, 5}});
  std::vector<int> n({2, 2, 2});

  auto funcPtr = std::make_unique<std::function<double(std::vector<double>)>>(f);
  auto limPtr = std::make_unique<std::vector<std::pair<double, double>>>(limits);
  auto nPtr = std::make_unique<std::vector<int>>(n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_seq::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  taskSequential.run();
  taskSequential.post_processing();
  ASSERT_NEAR(283.5, out[0], 0.1);

  delete reinterpret_cast<std::function<double(std::vector<double>)> *>(taskDataSeq->inputs[0]);
  delete reinterpret_cast<std::vector<std::pair<double, double>> *>(taskDataSeq->inputs[1]);
  delete reinterpret_cast<std::vector<int> *>(taskDataSeq->inputs[2]);
}

TEST(fedorets_i_simpson_seq, Func_4) {
  // Create data
  std::vector<double> out(1, 0);

  const std::function<double(std::vector<double>)> f = [](std::vector<double> vec) {
    double x = vec[0];
    double y = vec[1];
    double z = vec[2];
    return exp(x) - sqrt(10) * 5 * sin(y) + cos(-2 * z * z);
  };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {0, 5}});
  std::vector<int> n({2, 2, 2});

  auto funcPtr = std::make_unique<std::function<double(std::vector<double>)>>(f);
  auto limPtr = std::make_unique<std::vector<std::pair<double, double>>>(limits);
  auto nPtr = std::make_unique<std::vector<int>>(n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_seq::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  taskSequential.run();
  taskSequential.post_processing();
  ASSERT_NEAR(111816.7, out[0], 0.1);

  delete reinterpret_cast<std::function<double(std::vector<double>)> *>(taskDataSeq->inputs[0]);
  delete reinterpret_cast<std::vector<std::pair<double, double>> *>(taskDataSeq->inputs[1]);
  delete reinterpret_cast<std::vector<int> *>(taskDataSeq->inputs[2]);
}

TEST(fedorets_i_simpson_seq, Func_5) {
  // Create data
  std::vector<double> out(1, 0);

  const std::function<double(std::vector<double>)> f = [](std::vector<double> vec) {
    double x = vec[0];
    double y = vec[1];
    double z = vec[2];
    return exp(x) + sqrt(2) * sin(y * z) + cos(z * z);
  };

  std::vector<std::pair<double, double>> limits({{1, 10}, {1, 3}, {0, 6}});
  std::vector<int> n({2, 2, 2});

  auto funcPtr = std::make_unique<std::function<double(std::vector<double>)>>(f);
  auto limPtr = std::make_unique<std::vector<std::pair<double, double>>>(limits);
  auto nPtr = std::make_unique<std::vector<int>>(n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.release()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_seq::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  taskSequential.run();
  taskSequential.post_processing();
  ASSERT_NEAR(287147.7, out[0], 0.1);

  delete reinterpret_cast<std::function<double(std::vector<double>)> *>(taskDataSeq->inputs[0]);
  delete reinterpret_cast<std::vector<std::pair<double, double>> *>(taskDataSeq->inputs[1]);
  delete reinterpret_cast<std::vector<int> *>(taskDataSeq->inputs[2]);
}