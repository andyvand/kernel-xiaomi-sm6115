/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (c) 2014-2015, 2017-2018 The Linux Foundation. All rights reserved.
 */

#ifndef DIAG_MEMORYDEVICE_H
#define DIAG_MEMORYDEVICE_H

#define DIAG_MD_LOCAL		0
#define DIAG_MD_LOCAL_LAST	1
#define DIAG_MD_BRIDGE_BASE	DIAG_MD_LOCAL_LAST
#define DIAG_MD_MDM		(DIAG_MD_BRIDGE_BASE)
#define DIAG_MD_MDM2		(DIAG_MD_BRIDGE_BASE + 1)
#define DIAG_MD_SMUX		(DIAG_MD_BRIDGE_BASE + 2)
#define DIAG_MD_BRIDGE_LAST	(DIAG_MD_BRIDGE_BASE + 3)

#ifndef CONFIG_DIAGFWD_BRIDGE_CODE
#define NUM_DIAG_MD_DEV		DIAG_MD_LOCAL_LAST
#else
#define NUM_DIAG_MD_DEV		DIAG_MD_BRIDGE_LAST
#endif

struct diag_buf_tbl_t {
	unsigned char *buf;
	int len;
	int ctx;
};

struct diag_md_info {
	int id;
	int ctx;
	int mempool;
	int num_tbl_entries;
	int md_info_inited;
	spinlock_t lock;
	struct diag_buf_tbl_t *tbl;
	struct diag_mux_ops *ops;
};

extern struct diag_md_info diag_md[NUM_DIAG_MD_DEV];

int diag_md_init(void);
int diag_md_mdm_init(void);
void diag_md_exit(void);
void diag_md_mdm_exit(void);
void diag_md_open_all(void);
void diag_md_close_all(void);
int diag_md_register(int id, int ctx, struct diag_mux_ops *ops);
int diag_md_close_peripheral(int id, uint8_t peripheral);
int diag_md_write(int id, unsigned char *buf, int len, int ctx);
int diag_md_copy_to_user(char __user *buf, int *pret, size_t buf_size,
			 struct diag_md_session_t *info);
#endif
