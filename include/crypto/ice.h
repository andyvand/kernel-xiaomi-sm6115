/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2019, The Linux Foundation. All rights reserved.
 */

#ifndef _QCOM_INLINE_CRYPTO_ENGINE_H_
#define _QCOM_INLINE_CRYPTO_ENGINE_H_

#include <linux/platform_device.h>

struct request;

enum ice_cryto_algo_mode {
	ICE_CRYPTO_ALGO_MODE_AES_ECB = 0x0,
	ICE_CRYPTO_ALGO_MODE_AES_XTS = 0x3,
};

enum ice_crpto_key_size {
	ICE_CRYPTO_KEY_SIZE_128 = 0x0,
	ICE_CRYPTO_KEY_SIZE_256 = 0x2,
};

enum ice_crpto_key_mode {
	ICE_CRYPTO_USE_KEY0_HW_KEY = 0x0,
	ICE_CRYPTO_USE_KEY1_HW_KEY = 0x1,
	ICE_CRYPTO_USE_LUT_SW_KEY0 = 0x2,
	ICE_CRYPTO_USE_LUT_SW_KEY  = 0x3
};

struct ice_crypto_setting {
	enum ice_crpto_key_size		key_size;
	enum ice_cryto_algo_mode	algo_mode;
	enum ice_crpto_key_mode		key_mode;
	short				key_index;

};

struct ice_data_setting {
	struct ice_crypto_setting	crypto_data;
	bool				sw_forced_context_switch;
	bool				decr_bypass;
	bool				encr_bypass;
};

/* MSM ICE Crypto Data Unit of target DUN of Transfer Request */
enum ice_crypto_data_unit {
	ICE_CRYPTO_DATA_UNIT_512_B          = 0,
	ICE_CRYPTO_DATA_UNIT_1_KB           = 1,
	ICE_CRYPTO_DATA_UNIT_2_KB           = 2,
	ICE_CRYPTO_DATA_UNIT_4_KB           = 3,
	ICE_CRYPTO_DATA_UNIT_8_KB           = 4,
	ICE_CRYPTO_DATA_UNIT_16_KB          = 5,
	ICE_CRYPTO_DATA_UNIT_32_KB          = 6,
	ICE_CRYPTO_DATA_UNIT_64_KB          = 7,
};

typedef void (*ice_error_cb)(void *, u32 error);

struct qcom_ice_variant_ops *qcom_ice_get_variant_ops(struct device_node *node);
struct platform_device *qcom_ice_get_pdevice(struct device_node *node);

#ifdef CONFIG_CRYPTO_DEV_QCOM_ICE
int qcom_ice_setup_ice_hw(const char *storage_type, int enable);
void qcom_ice_set_fde_flag(int flag);
#else
static inline int qcom_ice_setup_ice_hw(const char *storage_type, int enable)
{
	return 0;
}
static inline void qcom_ice_set_fde_flag(int flag) {}
#endif

struct qcom_ice_variant_ops {
	const char *name;
	int	(*init)(struct platform_device *device_init, void *init_data,
				ice_error_cb err);
	int	(*reset)(struct platform_device *device_reset);
	int	(*resume)(struct platform_device *device_resume);
	int	(*suspend)(struct platform_device *device_suspend);
	int	(*config_start)(struct platform_device *device_start,
			struct request *req, struct ice_data_setting *setting,
			bool start);
	int	(*config_end)(struct request *req);
	int	(*status)(struct platform_device *device_status);
	void	(*debug)(struct platform_device *device_debug);
};

#endif /* _QCOM_INLINE_CRYPTO_ENGINE_H_ */
