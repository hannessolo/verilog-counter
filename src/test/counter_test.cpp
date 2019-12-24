#include "counter.h"
#include "counter_counter_types.h"
#include "verilated.h"

struct TestCase {
  const char* name;
  uint8_t reset;
  uint8_t cmd;
  uint16_t load_addr;
  uint16_t expected_addr;
};

TestCase test_cases[] {
  { "reset", 1, counter_counter_types::cmd_t::NONE, 0, 0 },
  { "load", 0, counter_counter_types::cmd_t::LOAD, 1234, 1234},
  { "increment", 0, counter_counter_types::cmd_t::INC, 0, 1235},
  { "reset", 1, counter_counter_types::cmd_t::NONE, 0, 0 }
};

int main(int argc, char** argv, char** env) {
  Verilated::commandArgs(argc, argv);
  counter* cnt = new counter;

  cnt->clk = 0;
  cnt->addr = 1234;
  cnt->reset = 0;
  cnt->cmd = counter_counter_types::cmd_t::NONE;
  cnt->load_addr = 0;
  cnt->eval();

  int num_test_cases = sizeof(test_cases) /  sizeof(TestCase);

  for (int k = 0; k < num_test_cases; k++) {
    TestCase* test_case = &test_cases[k];

    cnt->cmd = test_case->cmd;
    cnt->reset = test_case->reset;
    cnt->load_addr = test_case->load_addr;
    cnt->eval();

    cnt->clk = 1;
    cnt->eval();
    cnt->clk = 0;
    cnt->eval();

    if (cnt->addr == test_case->expected_addr) {
      printf("%s: Passed\n", test_case->name);
    } else {
      printf("%s: Failed. Expected %d, got %d.\n", test_case->name, test_case->expected_addr, cnt->addr);
    }
  }
  cnt->final();
  delete cnt;
}
