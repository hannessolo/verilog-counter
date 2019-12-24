module cpu (
  input logic clk,
  input logic[7:0] instruction,
  output logic[10:0] fetchaddr,
  output logic[7:0] result
);

  logic[7:0] instr;
  logic[7:0] a;
  logic[7:0] b;
  logic zf;
  alu_types::alu_t aluinst;

  counter cnt(clk, 0, counter_types::INC, 0, fetchaddr);

  // Fetch
  always_ff @(posedge clk) begin
    instr <= instruction;
  end

  // Decode
  always_comb begin
    unique case(instr[1:0])
      0:
        aluinst = alu_types::ADD;
      1:
        aluinst = alu_types::SUB;
      2:
        aluinst = alu_types::OR;
      3:
        aluinst = alu_types::AND;
      default:
        aluinst = alu_types::ADD;
    endcase

    a = 5;
    b = 6;
  end

  // Execute
  alu alu1(aluinst, a, b, zf, result);

endmodule
