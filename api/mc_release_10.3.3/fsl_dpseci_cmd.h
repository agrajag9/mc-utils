/* Copyright 2013-2017 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * * Neither the name of the above-listed copyright holders nor the
 * names of any contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_DPSECI_CMD_H
#define _FSL_DPSECI_CMD_H

/* DPSECI Version */
#define DPSECI_VER_MAJOR		5
#define DPSECI_VER_MINOR		1

/* Command versioning */
#define DPSECI_CMD_BASE_VERSION		1
#define DPSECI_CMD_BASE_VERSION_V2	2
#define DPSECI_CMD_ID_OFFSET		4

#define DPSECI_CMD_V1(id)	((id << DPSECI_CMD_ID_OFFSET) | DPSECI_CMD_BASE_VERSION)
#define DPSECI_CMD_V2(id)	((id << DPSECI_CMD_ID_OFFSET) | DPSECI_CMD_BASE_VERSION_V2)

/* Command IDs */
#define DPSECI_CMDID_CLOSE		DPSECI_CMD_V1(0x800)
#define DPSECI_CMDID_OPEN		DPSECI_CMD_V1(0x809)
#define DPSECI_CMDID_CREATE		DPSECI_CMD_V2(0x909)
#define DPSECI_CMDID_DESTROY		DPSECI_CMD_V1(0x989)
#define DPSECI_CMDID_GET_API_VERSION	DPSECI_CMD_V1(0xa09)

#define DPSECI_CMDID_ENABLE		DPSECI_CMD_V1(0x002)
#define DPSECI_CMDID_DISABLE		DPSECI_CMD_V1(0x003)
#define DPSECI_CMDID_GET_ATTR		DPSECI_CMD_V1(0x004)
#define DPSECI_CMDID_RESET		DPSECI_CMD_V1(0x005)
#define DPSECI_CMDID_IS_ENABLED		DPSECI_CMD_V1(0x006)

#define DPSECI_CMDID_SET_IRQ_ENABLE	DPSECI_CMD_V1(0x012)
#define DPSECI_CMDID_GET_IRQ_ENABLE	DPSECI_CMD_V1(0x013)
#define DPSECI_CMDID_SET_IRQ_MASK	DPSECI_CMD_V1(0x014)
#define DPSECI_CMDID_GET_IRQ_MASK	DPSECI_CMD_V1(0x015)
#define DPSECI_CMDID_GET_IRQ_STATUS	DPSECI_CMD_V1(0x016)
#define DPSECI_CMDID_CLEAR_IRQ_STATUS	DPSECI_CMD_V1(0x017)

#define DPSECI_CMDID_SET_RX_QUEUE	DPSECI_CMD_V1(0x194)
#define DPSECI_CMDID_GET_RX_QUEUE	DPSECI_CMD_V1(0x196)
#define DPSECI_CMDID_GET_TX_QUEUE	DPSECI_CMD_V1(0x197)
#define DPSECI_CMDID_GET_SEC_ATTR	DPSECI_CMD_V1(0x198)
#define DPSECI_CMDID_GET_SEC_COUNTERS	DPSECI_CMD_V1(0x199)
#define DPSECI_CMDID_SET_OPR		DPSECI_CMD_V1(0x19A)
#define DPSECI_CMDID_GET_OPR		DPSECI_CMD_V1(0x19B)
#define DPSECI_CMDID_SET_CONGESTION_NOTIFICATION	DPSECI_CMD_V1(0x170)
#define DPSECI_CMDID_GET_CONGESTION_NOTIFICATION	DPSECI_CMD_V1(0x171)


/* Macros for accessing command fields smaller than 1byte */
#define DPSECI_MASK(field)        \
	GENMASK(DPSECI_##field##_SHIFT + DPSECI_##field##_SIZE - 1, \
		DPSECI_##field##_SHIFT)
#define dpseci_set_field(var, field, val) \
	((var) |= (((val) << DPSECI_##field##_SHIFT) & DPSECI_MASK(field)))
#define dpseci_get_field(var, field)      \
	(((var) & DPSECI_MASK(field)) >> DPSECI_##field##_SHIFT)

#pragma pack(push, 1)
struct dpseci_cmd_open {
	uint32_t dpseci_id;
};

struct dpseci_cmd_create {
	uint8_t priorities[8];
	uint8_t num_tx_queues;
	uint8_t num_rx_queues;
	uint8_t pad[6];
	uint32_t options;
};

struct dpseci_cmd_destroy {
	uint32_t dpseci_id;
};

#define DPSECI_ENABLE_SHIFT	0
#define DPSECI_ENABLE_SIZE	1

struct dpseci_rsp_is_enabled {
	/* only the first LSB */
	uint8_t en;
};

struct dpseci_cmd_get_irq {
	uint32_t pad;
	uint8_t irq_index;
};

struct dpseci_cmd_set_irq_enable {
	uint8_t enable_state;
	uint8_t pad[3];
	uint8_t irq_index;
};

struct dpseci_rsp_get_irq_enable {
	uint8_t enable_state;
};

struct dpseci_cmd_set_irq_mask {
	uint32_t mask;
	uint8_t irq_index;
};

struct dpseci_rsp_get_irq_mask {
	uint32_t mask;
};

struct dpseci_cmd_irq_status {
	uint32_t status;
	uint8_t irq_index;
};

struct dpseci_rsp_get_irq_status {
	uint32_t status;
};

struct dpseci_rsp_get_attr {
	uint32_t id;
	uint32_t pad;
	uint8_t num_tx_queues;
	uint8_t num_rx_queues;
	uint8_t pad1[6];
	uint32_t options;
};

#define DPSECI_DEST_TYPE_SHIFT	0
#define DPSECI_DEST_TYPE_SIZE	4

#define DPSECI_ORDER_PRESERVATION_SHIFT	0
#define DPSECI_ORDER_PRESERVATION_SIZE	1

struct dpseci_cmd_set_rx_queue {
	uint32_t dest_id;
	uint8_t dest_priority;
	uint8_t queue;
	/* from LSB: dest_type:4 */
	uint8_t dest_type;
	uint8_t pad;
	uint64_t user_ctx;
	uint32_t options;
	/* only the LSB */
	uint8_t order_preservation_en;
};

struct dpseci_cmd_get_queue {
	uint8_t pad[5];
	uint8_t queue;
};

struct dpseci_rsp_get_rx_queue {
	uint32_t dest_id;
	uint8_t dest_priority;
	uint8_t pad1;
	/* from LSB: dest_type:4 */
	uint8_t dest_type;
	uint8_t pad2;
	uint64_t user_ctx;
	uint32_t fqid;
	/* only the LSB */
	uint8_t order_preservation_en;

};

struct dpseci_rsp_get_tx_queue {
	uint32_t pad;
	uint32_t fqid;
	uint8_t priority;
};

struct dpseci_rsp_get_sec_attr {
	uint16_t ip_id;
	uint8_t major_rev;
	uint8_t minor_rev;
	uint8_t era;
	uint8_t pad1[3];
	uint8_t deco_num;
	uint8_t zuc_auth_acc_num;
	uint8_t zuc_enc_acc_num;
	uint8_t pad2;
	uint8_t snow_f8_acc_num;
	uint8_t snow_f9_acc_num;
	uint8_t crc_acc_num;
	uint8_t pad3;
	uint8_t pk_acc_num;
	uint8_t kasumi_acc_num;
	uint8_t rng_acc_num;
	uint8_t pad4;
	uint8_t md_acc_num;
	uint8_t arc4_acc_num;
	uint8_t des_acc_num;
	uint8_t aes_acc_num;
};

struct dpseci_rsp_get_sec_counters {
	uint64_t dequeued_requests;
	uint64_t ob_enc_requests;
	uint64_t ib_dec_requests;
	uint64_t ob_enc_bytes;
	uint64_t ob_prot_bytes;
	uint64_t ib_dec_bytes;
	uint64_t ib_valid_bytes;
};

struct dpseci_rsp_get_api_version {
	uint16_t major;
	uint16_t minor;
};

struct dpseci_cmd_set_opr {
	uint16_t pad0;
	uint8_t index;
	uint8_t options;
	uint8_t pad1[7];
	uint8_t oloe;
	uint8_t oeane;
	uint8_t olws;
	uint8_t oa;
	uint8_t oprrws;
};

struct dpseci_cmd_get_opr {
	uint16_t pad;
	uint8_t index;
};

#define DPSECI_RIP_SHIFT	0
#define DPSECI_RIP_SIZE		1
#define DPSECI_OPR_ENABLE_SHIFT	1
#define DPSECI_OPR_ENABLE_SIZE	1
#define DPSECI_TSEQ_NLIS_SHIFT	0
#define DPSECI_TSEQ_NLIS_SIZE	1
#define DPSECI_HSEQ_NLIS_SHIFT	0
#define DPSECI_HSEQ_NLIS_SIZE	1

struct dpseci_rsp_get_opr {
	uint64_t pad0;
	/* from LSB: rip:1 enable:1 */
	uint8_t flags;
	uint16_t pad1;
	uint8_t oloe;
	uint8_t oeane;
	uint8_t olws;
	uint8_t oa;
	uint8_t oprrws;
	uint16_t nesn;
	uint16_t pad8;
	uint16_t ndsn;
	uint16_t pad2;
	uint16_t ea_tseq;
	/* only the LSB */
	uint8_t tseq_nlis;
	uint8_t pad3;
	uint16_t ea_hseq;
	/* only the LSB */
	uint8_t hseq_nlis;
	uint8_t pad4;
	uint16_t ea_hptr;
	uint16_t pad5;
	uint16_t ea_tptr;
	uint16_t pad6;
	uint16_t opr_vid;
	uint16_t pad7;
	uint16_t opr_id;
};

#define DPSECI_DEST_TYPE_SHIFT		0
#define DPSECI_DEST_TYPE_SIZE		4
#define DPSECI_CG_UNITS_SHIFT		4
#define DPSECI_CG_UNITS_SIZE		2

struct dpseci_cmd_set_congestion_notification {
	uint32_t dest_id;
	uint16_t notification_mode;
	uint8_t dest_priority;
	/* from LSB: dest_type: 4 units:2 */
	uint8_t type_units;
	uint64_t message_iova;
	uint64_t message_ctx;
	uint32_t threshold_entry;
	uint32_t threshold_exit;
};
#pragma pack(pop)
#endif /* _FSL_DPSECI_CMD_H */