/*
 * Copyright (C) 2019-2021 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */
#pragma once

/**
 * @defgroup    pkg_nimble_rpble_connect Connection establishment for rpble
 * @ingroup     pkg_nimble_rpble
 * @brief       Optional helper module for establishing BLE connections analogous
 *              to the RPL tree.
 * @{
 *
 * @file
 * @brief       Connection establishment for RPL-over-BLE (rpble)
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Initialize the nimble_rpble_connect module with the given parameters
 *
 * @note    This function is meant to be called only once, by the nimble rpble implementation
 *
 * @param[in] cfg       configuration parameters
 *
 * @return  0 on success
 */
void nimble_rpble_connect_init(void);

/**
 * @brief   Update the used timing parameters
 *
 * @note    This function is meant to be called only by the nimble rpble implementation
 *
 * @param[in] cfg       configuration parameters
 *
 * @return  0 on success
 */
void nimble_rpble_connect_param_update(const nimble_rpble_cfg_t *cfg);

/**
 * @brief   Handle a netif event
 *
 * @note    This function is meant to be called only by the nimble rpble implementation
 *
 * @param[in] handle       handle to the connection that triggered the event
 * @param[in] event        type of the event
 * @param[in] addr         BLE address of the peer in the affected connection
 *
 * @return  0 on success
 */
void nimble_rpble_connect_on_netif_event(int handle, 
                                         nimble_netif_event_t event, 
                                         const uint8_t *addr);

/**
 * @brief   Update the current RPL context
 *
 * @note    This function is meant to be called only by the nimble rpble implementation
 *
 * @param[in] ctx       current DODAG state

 * @return  0 on success
 * @return  -EALREADY if the given context did not change
 */
int nimble_rpble_connect_update(const nimble_rpble_ctx_t *ctx);

#ifdef __cplusplus
}
#endif

/** @} */
