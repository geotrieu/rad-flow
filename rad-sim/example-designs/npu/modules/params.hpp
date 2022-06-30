#pragma once

// Key NPU Architecture Parameters
#define CORES 2
#define TILES 7
#define SECTORS 10
#define DPES_PER_SECTOR 4
#define LANES 40
#define THREADS 1
#define VRF_DEPTH 1024
#define MRF_DEPTH 2048
#define DATA_FIFO_DEPTH 512
#define INST_MEMORY_DEPTH 512
#define MOP_FIFO_DEPTH 512
#define MOP_FIFO_ALMOST_FULL_DEPTH (MOP_FIFO_DEPTH - 10)
#define UOP_FIFO_DEPTH 512
#define UOP_FIFO_ALMOST_FULL_DEPTH (UOP_FIFO_DEPTH - 10)
#define NPU_CLOCK_PERIOD FABRIC_PERIOD
#define MAX_TAG 512
#define TB_LANES 10
#define TB_NUM_DOTS 3

// Precisions Definition
#define LOW_PRECISION 8
#define HIGH_PRECISION 32
typedef sc_int<LOW_PRECISION> tb_input_precision;
typedef sc_int<HIGH_PRECISION> tb_output_precision;

// Latency Parameters
#define RF_RD_LATENCY 2
#define RF_WR_LATENCY 1
#define TB_LATENCY 3
#define SECTOR_DISTRIBUTION_PIPELINE 2
#define SECTOR_REDUCTION_PIPELINE 3
#define SECTOR_REDUCTION_TO_ACCUM_PIPELINE 2
#define SECTOR_ACCUM_TO_OFIFO_PIPELINE 2
#define EVRF_INST_TO_VRF 4
#define EVRF_RF_TO_OFIFO_PIPELINE 2
#define MFU_INST_TO_VRFS_PIPLINE 2
#define MFU_VRFS_TO_COMPUTE_PIPELINE 9
#define MFU_ACT_LATENCY 3
#define MFU_ADD_LATENCY 1
#define MFU_MUL_LATENCY 6
#define MFU_COMPUTE_TO_OFIFO_PIPELINE 2
#define LD_PIPELINE 8

// Signal Width Parameters
#define VRF_ADDRW 10
#define MRF_ADDRW 11
#define NSIZEW 11
#define VRFIDW 2
#define MRFIDW 9
#define ACCUMIDW 5
#define TAGW 10
#define BATCH_COUNTW 2
#define BLOCK_COUNTW 4
#define ACCUM_OPW 2
#define BLOCK_WB_SELW 8
#define VRF_WB_SELW 4

// Derived Parameters (do not change unless you really know why)
#define DPE_NUM_TBS ((int)ceil(LANES * 1.0 / TB_LANES) + 1)
#define DPE_USE_SEL_PIPELINE ((TB_LATENCY - 1) * (DPE_NUM_TBS - 2))
#define DPE_VALID_A_PIPELINE (TB_LATENCY + (DPE_NUM_TBS - 2) * (TB_LATENCY - 1))
#define DPE_VALID_B_PIPELINE (DPE_NUM_TBS * TB_NUM_DOTS)
#define DPE_SHIFT_SEL_PIPELINE (DPE_NUM_TBS * TB_NUM_DOTS)
#define DPE_VECTOR_A_PIPELINE ((DPE_NUM_TBS - 2) * (TB_LATENCY - 1))
#define MRF_ADDR_PIPELINE (2 * (DPE_NUM_TBS - 1))
#define SECTOR_MRF_ADDR_PIPELINE (SECTOR_DISTRIBUTION_PIPELINE + (DPE_NUM_TBS * TB_NUM_DOTS) - 1)
#define SECTOR_MRF_DATA_PIPELINE RF_RD_LATENCY
#define SECTOR_VRF_DATA_PIPELINE SECTOR_DISTRIBUTION_PIPELINE
#define SECTOR_INST_TO_DPES_PIPELINE (SECTOR_MRF_ADDR_PIPELINE + SECTOR_MRF_DATA_PIPELINE)
#define SECTOR_DPES_PIPELINE DPE_VALID_A_PIPELINE
#define SECTOR_INST_TO_ACCUM_PIPELINE (SECTOR_INST_TO_DPES_PIPELINE + SECTOR_DPES_PIPELINE + SECTOR_REDUCTION_PIPELINE + SECTOR_REDUCTION_TO_ACCUM_PIPELINE)
#define ACCUM_PIPELINE (RF_RD_LATENCY + 1)
#define SECTOR_INST_PIPELINE (SECTOR_INST_TO_DPES_PIPELINE + SECTOR_DPES_PIPELINE + SECTOR_REDUCTION_PIPELINE + SECTOR_REDUCTION_TO_ACCUM_PIPELINE + ACCUM_PIPELINE + SECTOR_ACCUM_TO_OFIFO_PIPELINE)
#define EVRF_INST_PIPELINE (EVRF_INST_TO_VRF + RF_RD_LATENCY + EVRF_RF_TO_OFIFO_PIPELINE)
#define EVRF_PIPELINE (EVRF_INST_TO_VRF + RF_RD_LATENCY + EVRF_RF_TO_OFIFO_PIPELINE)
#define MFU_COMPUTE_PIPELINE (MFU_ACT_LATENCY + MFU_ADD_LATENCY + MFU_MUL_LATENCY)
#define MFU_INST_PIPELINE (MFU_INST_TO_VRFS_PIPLINE + RF_RD_LATENCY + MFU_VRFS_TO_COMPUTE_PIPELINE)
#define MFU_INPUT_TO_COMPUTE_PIPELINE (MFU_INST_TO_VRFS_PIPLINE + RF_RD_LATENCY + MFU_VRFS_TO_COMPUTE_PIPELINE)
#define MFU_PIPELINE (MFU_INPUT_TO_COMPUTE_PIPELINE + MFU_COMPUTE_PIPELINE + MFU_COMPUTE_TO_OFIFO_PIPELINE)
#define NUM_PIPELINE_BLOCKS 5
#define NUM_VRFS (TILES + 5)
#define NUM_ACCUM ((DPE_NUM_TBS - 1) * TB_NUM_DOTS)
#define NAME_LENGTH 35

// AXI-S Parameters
#define FEEDFORWARD_DATA_WIDTH (CORES * DPES_PER_SECTOR * HIGH_PRECISION)
#define WIDE_WRITEBACK_WIDTH (CORES * LANES * LOW_PRECISION)
#define WIDE_WRITEBACK_BV_WIDTH ((CORES * LANES * LOW_PRECISION) + VRF_WB_SELW + VRF_ADDRW + 1)
#define NARROW_WRITEBACK_WIDTH (CORES * DPES_PER_SECTOR * HIGH_PRECISION)
#define NARROW_WRITEBACK_BV_WIDTH ((CORES * DPES_PER_SECTOR * HIGH_PRECISION) + VRF_WB_SELW + BLOCK_WB_SELW + VRF_ADDRW + 1)
#define AXIS_ADAPTER_BUFFER_CAPACITY 2
#define TDATA(bv) (bv.range(AXIS_MAX_DATAW - 1, 0))
#define TSTRB(bv) (bv.range(AXIS_MAX_DATAW + AXIS_STRBW - 1, AXIS_MAX_DATAW))
#define TKEEP(bv) (bv.range(AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW - 1, AXIS_MAX_DATAW + AXIS_STRBW))
#define TUSER(bv) (bv.range(AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW + AXIS_USERW - 1, AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW))
#define TUSER_FLAG(bv) (bv.range(AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW, AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW))
#define TUSER_ADDR(bv) (bv.range(AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW + VRF_ADDRW, AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW + 1))
#define TUSER_VRFID(bv) (bv.range(AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW + AXIS_USERW - 1, AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW + VRF_ADDRW + 1))
#define TDEST(bv) (bv.range(AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW + AXIS_USERW + AXIS_DESTW - 1, AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW + AXIS_USERW))
#define TID(bv) (bv.range(AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW + AXIS_USERW + AXIS_DESTW + AXIS_IDW - 1, AXIS_MAX_DATAW + AXIS_STRBW + AXIS_KEEPW + AXIS_USERW + AXIS_DESTW))
#define TLAST(bv) (bv.range(AXIS_TRANSACTION_WIDTH - 1, AXIS_TRANSACTION_WIDTH - 1))

// Trace Probe IDs
#define UOP_ISSUE_TRACE 0
#define UOP_RETIRE_TRACE 1
#define FIRST_UOP_ISSUE_TRACE 2
#define LAST_UOP_RETIRE_TRACE 3
#define TAG_UPDATE_TRACE 4
