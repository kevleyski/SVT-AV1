/*
* Copyright(c) 2019 Netflix, Inc.
*
* This source code is subject to the terms of the BSD 2 Clause License and
* the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
* was not distributed with this source code in the LICENSE file, you can
* obtain it at https://www.aomedia.org/license/software-license. If the Alliance for Open
* Media Patent License 1.0 was not distributed with this source code in the
* PATENTS file, you can obtain it at https://www.aomedia.org/license/patent-license.
*/

#ifndef EbDecInverseQuantize_h
#define EbDecInverseQuantize_h

#include "EbAv1Structs.h"
#include "EbDecProcessFrame.h"

int16_t svt_aom_dc_quant_qtx(int32_t qindex, int32_t delta, EbBitDepth bit_depth);
int16_t svt_aom_ac_quant_qtx(int32_t qindex, int32_t delta, EbBitDepth bit_depth);

void    svt_aom_setup_segmentation_dequant(DecModCtxt *dec_mod_ctxt);
void    svt_aom_inverse_qm_init(DecModCtxt *dec_mod_ctxt, SeqHeader *seq_header);
void    svt_aom_update_dequant(DecModCtxt *dec_mod_ctxt, SBInfo *sb_info);
int32_t svt_aom_inverse_quantize(DecModCtxt *dec_mod_ctxt, PartitionInfo *part, BlockModeInfo *mode, int32_t *level,
                                 int32_t *qcoeffs, TxType tx_type, TxSize tx_size, int plane);

#endif // EbDecInverseQuantize_h
