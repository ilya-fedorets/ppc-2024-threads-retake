// Copyright 2024 Fedorets Ilia

#include <gtest/gtest.h>

#include <vector>

#include "omp/fedorets_i_simpson/include/simpson.hpp"

TEST(fedorets_i_simpson_omp, Func_1) {
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
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  std::chrono::steady_clock::time_point begin_seq = std::chrono::steady_clock::now();
  taskSequential.run();
  std::chrono::steady_clock::time_point end_seq = std::chrono::steady_clock::now();
  taskSequential.post_processing();
  ASSERT_NEAR(294, out[0], 0.1);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);

  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataParallel->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonParallel taskParallel(taskDataParallel);
  ASSERT_EQ(taskParallel.validation(), true);
  taskParallel.pre_processing();
  std::chrono::steady_clock::time_point begin_par = std::chrono::steady_clock::now();
  taskParallel.run();
  std::chrono::steady_clock::time_point end_par = std::chrono::steady_clock::now();
  taskParallel.post_processing();
  ASSERT_NEAR(294, out[0], 0.1);

  std::cout << "Seq    time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_seq - begin_seq).count() << std::endl;
  std::cout << "OpenMP time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_par - begin_par).count() << std::endl;
}

TEST(fedorets_i_simpson_omp, Func_2) {
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
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  std::chrono::steady_clock::time_point begin_seq = std::chrono::steady_clock::now();
  taskSequential.run();
  std::chrono::steady_clock::time_point end_seq = std::chrono::steady_clock::now();
  taskSequential.post_processing();
  ASSERT_NEAR(203.7, out[0], 0.1);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);

  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataParallel->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonParallel taskParallel(taskDataParallel);
  ASSERT_EQ(taskParallel.validation(), true);
  taskParallel.pre_processing();
  std::chrono::steady_clock::time_point begin_par = std::chrono::steady_clock::now();
  taskParallel.run();
  std::chrono::steady_clock::time_point end_par = std::chrono::steady_clock::now();
  taskParallel.post_processing();
  ASSERT_NEAR(203.7, out[0], 0.1);

  std::cout << "Seq    time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_seq - begin_seq).count() << std::endl;
  std::cout << "OpenMP time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_par - begin_par).count() << std::endl;
}

TEST(fedorets_i_simpson_omp, Func_3) {
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
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  std::chrono::steady_clock::time_point begin_seq = std::chrono::steady_clock::now();
  taskSequential.run();
  std::chrono::steady_clock::time_point end_seq = std::chrono::steady_clock::now();
  taskSequential.post_processing();
  ASSERT_NEAR(283.5, out[0], 0.1);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);

  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataParallel->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonParallel taskParallel(taskDataParallel);
  ASSERT_EQ(taskParallel.validation(), true);
  taskParallel.pre_processing();
  std::chrono::steady_clock::time_point begin_par = std::chrono::steady_clock::now();
  taskParallel.run();
  std::chrono::steady_clock::time_point end_par = std::chrono::steady_clock::now();
  taskParallel.post_processing();
  ASSERT_NEAR(283.5, out[0], 0.1);

  std::cout << "Seq    time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_seq - begin_seq).count() << std::endl;
  std::cout << "OpenMP time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_par - begin_par).count() << std::endl;
}

TEST(fedorets_i_simpson_omp, Func_4) {
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
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  std::chrono::steady_clock::time_point begin_seq = std::chrono::steady_clock::now();
  taskSequential.run();
  std::chrono::steady_clock::time_point end_seq = std::chrono::steady_clock::now();
  taskSequential.post_processing();
  ASSERT_NEAR(111816.7, out[0], 0.1);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);

  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataParallel->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonParallel taskParallel(taskDataParallel);
  ASSERT_EQ(taskParallel.validation(), true);
  taskParallel.pre_processing();
  std::chrono::steady_clock::time_point begin_par = std::chrono::steady_clock::now();
  taskParallel.run();
  std::chrono::steady_clock::time_point end_par = std::chrono::steady_clock::now();
  taskParallel.post_processing();
  ASSERT_NEAR(111816.7, out[0], 0.1);

  std::cout << "Seq    time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_seq - begin_seq).count() << std::endl;
  std::cout << "OpenMP time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_par - begin_par).count() << std::endl;
}

TEST(fedorets_i_simpson_omp, Func_5) {
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
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataSeq->inputs_count.emplace_back(1);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonSequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  taskSequential.pre_processing();
  std::chrono::steady_clock::time_point begin_seq = std::chrono::steady_clock::now();
  taskSequential.run();
  std::chrono::steady_clock::time_point end_seq = std::chrono::steady_clock::now();
  taskSequential.post_processing();
  ASSERT_NEAR(287147.7, out[0], 0.1);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(funcPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(limPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(nPtr.get()));
  taskDataParallel->inputs_count.emplace_back(1);

  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataParallel->outputs_count.emplace_back(out.size());

  // Create Task
  fedorets_i_simpson_omp::SimpsonParallel taskParallel(taskDataParallel);
  ASSERT_EQ(taskParallel.validation(), true);
  taskParallel.pre_processing();
  std::chrono::steady_clock::time_point begin_par = std::chrono::steady_clock::now();
  taskParallel.run();
  std::chrono::steady_clock::time_point end_par = std::chrono::steady_clock::now();
  taskParallel.post_processing();
  ASSERT_NEAR(287147.7, out[0], 0.1);

  std::cout << "Seq    time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_seq - begin_seq).count() << std::endl;
  std::cout << "OpenMP time [µs]: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end_par - begin_par).count() << std::endl;
}
