/*
 * Copyright (C) 2019-2021 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     pkg_nimble_rpble
 * @{
 *
 * @file
 * @brief       RPL-over-BLE (rpble) implementation for NimBLE and GNRC
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#ifndef CONFIG_RPBLE_CONNECT
#  define CONFIG_RPBLE_CONNECT 1
#endif

#include "net/gnrc/rpl.h"

#include "nimble_netif.h"
#include "nimble_rpble.h"
#include "host/ble_gap.h"

#if CONFIG_RPBLE_CONNECT
#  include "nimble_rpble_connect.h"
#endif

#define ENABLE_DEBUG        0
#include "debug.h"

static nimble_netif_eventcb_t _eventcb = NULL;

static void _on_netif_evt(int handle, nimble_netif_event_t event,
                          const uint8_t *addr)
{
    switch (event) {
        case NIMBLE_NETIF_CONNECTED_MASTER:
            /* send a DIS once connected to a (new) node) */
            gnrc_rpl_send_DIS(NULL, (ipv6_addr_t *) &ipv6_addr_all_rpl_nodes,
                              NULL, 0);
            break;    
#if !CONFIG_RPBLE_CONNECT
        case NIMBLE_NETIF_CONNECTED_SLAVE:
            /* send a DIS once connected to a (new) node) */
            gnrc_rpl_send_DIS(NULL, (ipv6_addr_t *) &ipv6_addr_all_rpl_nodes,
                              NULL, 0);
            break;
#endif
        default:
            /* nothing to do for all other events */
            break;
    }
#if CONFIG_RPBLE_CONNECT
    nimble_rpble_connect_on_netif_event(handle, event, addr);
#endif

    /* pass events to high-level user if activated */
    if (_eventcb) {
        _eventcb(handle, event, addr);
    }
}

int nimble_rpble_init(const nimble_rpble_cfg_t *cfg)
{

#if CONFIG_RPBLE_CONNECT
    nimble_rpble_connect_init();
#endif

    return nimble_rpble_param_update(cfg);
}

int nimble_rpble_param_update(const nimble_rpble_cfg_t *cfg)
{

#if CONFIG_RPBLE_CONNECT
    nimble_rpble_connect_param_update(cfg);
#endif

    /* register event callback */
    nimble_netif_eventcb(_on_netif_evt);

    return 0;
}

int nimble_rpble_eventcb(nimble_netif_eventcb_t cb)
{
    _eventcb = cb;
    return 0;
}

int nimble_rpble_update(const nimble_rpble_ctx_t *ctx)
{
    
#if CONFIG_RPBLE_CONNECT
    return nimble_rpble_connect_update(ctx);
#endif

    return 0;
}
