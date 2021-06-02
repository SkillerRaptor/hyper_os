#pragma once

#include <stdint.h>

namespace Kernel
{
	class ACPI
	{
	public:
		struct RSDP
		{
			char signature[8];
			uint8_t checksum;
			char oem_id[6];
			uint8_t revision;
			uint32_t rsdt_address;
			
			uint32_t length;
			uint64_t xsdt_address;
			uint8_t extended_checksum;
			uint8_t reserved[3];
		} __attribute__((packed));
	
		struct SDT
		{
			char signature[4];
			uint32_t length;
			uint8_t revision;
			uint8_t checksum;
			char oem_id[6];
			char oem_table_id[8];
			uint32_t oem_revision;
			uint32_t creator_id;
			uint32_t creator_revision;
		};
		
	private:
		struct RSDT
		{
			SDT sdt;
			char pointer_start[];
		};
		
	public:
		static void initialize(RSDP* rsdp);
	
	private:
		static void detect_rsdt(RSDP* rsdp);
	
	private:
		static bool s_use_xsdt;
		static RSDT* s_rsdt;
	};
}