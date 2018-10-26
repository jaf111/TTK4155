#include "bluetooth.h"
#include <string.h>

#include "nrf_sdm.h"
#include "ble.h"
#include "ble_gap.h"

extern uint8_t __data_start__;

#define 	BLE_GAP_AD_TYPE_FLAGS   0x01
#define 	BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_MORE_AVAILABLE   0x02
#define 	BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE   0x03
#define 	BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_MORE_AVAILABLE   0x04
#define 	BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_COMPLETE   0x05
#define 	BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_MORE_AVAILABLE   0x06
#define 	BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_COMPLETE   0x07
#define 	BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME   0x08
#define 	BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME   0x09
#define 	BLE_GAP_AD_TYPE_TX_POWER_LEVEL   0x0A
#define 	BLE_GAP_AD_TYPE_CLASS_OF_DEVICE   0x0D
#define 	BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C   0x0E
#define 	BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R   0x0F
#define 	BLE_GAP_AD_TYPE_SECURITY_MANAGER_TK_VALUE   0x10
#define 	BLE_GAP_AD_TYPE_SECURITY_MANAGER_OOB_FLAGS   0x11
#define 	BLE_GAP_AD_TYPE_SLAVE_CONNECTION_INTERVAL_RANGE   0x12
#define 	BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_16BIT   0x14
#define 	BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_128BIT   0x15
#define 	BLE_GAP_AD_TYPE_SERVICE_DATA   0x16
#define 	BLE_GAP_AD_TYPE_PUBLIC_TARGET_ADDRESS   0x17
#define 	BLE_GAP_AD_TYPE_RANDOM_TARGET_ADDRESS   0x18
#define 	BLE_GAP_AD_TYPE_APPEARANCE   0x19
#define 	BLE_GAP_AD_TYPE_ADVERTISING_INTERVAL   0x1A
#define 	BLE_GAP_AD_TYPE_LE_BLUETOOTH_DEVICE_ADDRESS   0x1B
#define 	BLE_GAP_AD_TYPE_LE_ROLE   0x1C
#define 	BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C256   0x1D
#define 	BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R256   0x1E
#define 	BLE_GAP_AD_TYPE_SERVICE_DATA_32BIT_UUID   0x20
#define 	BLE_GAP_AD_TYPE_SERVICE_DATA_128BIT_UUID   0x21
#define 	BLE_GAP_AD_TYPE_URI   0x24
#define 	BLE_GAP_AD_TYPE_3D_INFORMATION_DATA   0x3D
#define 	BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA   0xFF



uint32_t bluetooth_init(){
	uint32_t err_code = 0;

	err_code = sd_softdevice_enable(NULL, NULL);
	if(err_code){
		return err_code;
	}

	static ble_enable_params_t ble_enable_params;
	memset(&ble_enable_params, 0, sizeof(ble_enable_params));
	uint32_t app_ram_base = (uint32_t)&__data_start__;

	ble_enable_params.gap_enable_params.periph_conn_count = 1;
	ble_enable_params.common_enable_params.vs_uuid_count = 1;

	err_code = sd_ble_enable(&ble_enable_params, &app_ram_base);
	return err_code;
}

uint32_t bluetooth_gap_advertise_start(){
	uint32_t err_code = 0;

	static uint8_t adv_data[] = {
		// Add some stuff
		//uint8_t const *p_data, uint8_t dlen, uint8_t const *p_sr_data, uint8_t srdlen
	};
	uint8_t adv_data_length = 0;

	// Add more stuff

	// Remove these lines when doing the GAP exercise
	(void)adv_data;
	(void)adv_data_length;

	return err_code;
}

uint32_t bluetooth_gatts_start(){
	uint32_t err_code = 0;

	return err_code;
}

void bluetooth_serve_forever(){
	// Comment all this in when doing GATT serving

	/*
	uint8_t ble_event_buffer[100] = {0};
	uint16_t ble_event_buffer_size = 100;

	while(1){
		if(m_matrix_attr_value != 0){
			// Matrix on
		}
		else{
			// Matrix off
		}

		while(
			sd_ble_evt_get(
				ble_event_buffer,
				&ble_event_buffer_size
			) != NRF_ERROR_NOT_FOUND
			){

			ble_evt_t * p_ble_event = (ble_evt_t *)ble_event_buffer;
			uint16_t event_id = p_ble_event->header.evt_id;

			switch(event_id){
				case BLE_GAP_EVT_CONNECTED:
					m_service_ubit.conn_handle =
						p_ble_event->evt.gap_evt.conn_handle;

					sd_ble_gatts_sys_attr_set(
						m_service_ubit.conn_handle,
						0,
						0,
						0
					);
					break;

				case BLE_GAP_EVT_DISCONNECTED:
					m_service_ubit.conn_handle =
						BLE_CONN_HANDLE_INVALID;

					bluetooth_gap_advertise_start();
					break;

				default:
					break;
			}

			ble_event_buffer_size = 100;
		}
		ble_event_buffer_size = 100;


	}
	*/
}
