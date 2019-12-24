module alu (
  input alu_types::alu_t op,
  input logic [7:0] a,
  input logic [7:0] b,
  output logic zf,
  output logic [7:0] res
);

  always_comb begin
    unique case(op)
      alu_types::ADD:
        res = a + b;
      alu_types::SUB:
        res = a - b;
      alu_types::OR:
        res = a | b;
      alu_types::AND:
        res = a & b;
      default:
        res = 0;
    endcase
    if (res == 0) zf = 1;
    else zf = 0;
  end


endmodule
