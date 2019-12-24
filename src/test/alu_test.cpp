#include "alu.h"

struct TestCase {
  const char* name;
  uint8_t op;
  uint8_t a;
  uint8_t b;
  uint8_t ex_z;
  uint8_t ex_res;
};

TestCase test_cases[] {
  { "add", 0, 1, 1, 0, 2 },
  { "sub", 1, 5, 3, 0, 2 },
  { "or", 2, 0b01, 0b10, 0, 0b11 },
  { "and", 3, 0b01, 0b11, 0, 0b01 },
  { "zf", 1, 5, 5, 1, 0 }
};

int main(int argc, char** argv, char** env) {
  Verilated::commandArgs(argc, argv);
  alu* alui = new alu;

  alui->a = 0;
  alui->b = 0;
  alui->eval();

  int num_test_cases = sizeof(test_cases) /  sizeof(TestCase);

  for (int k = 0; k < num_test_cases; k++) {
    TestCase* test_case = &test_cases[k];

    alui->a = test_case->a;
    alui->b = test_case->b;
    alui->op = test_case->op;
    alui->eval();

    if (alui->res == test_case->ex_res) {
      printf("%s: Passed\n", test_case->name);
    } else {
      printf("%s: Failed. Expected %d, got %d.\n", test_case->name, test_case->ex_res, alui->res);
    }
  }
  alui->final();
  delete alui;
}
