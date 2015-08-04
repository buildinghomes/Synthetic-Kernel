/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/irqdomain.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/of_fdt.h>
#include <linux/of_irq.h>
#include <linux/memory.h>
#include <linux/regulator/qpnp-regulator.h>
#include <linux/msm_tsens.h>
#include <asm/mach/map.h>
#include <asm/hardware/gic.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>
#include <mach/board.h>
#include <mach/gpiomux.h>
#include <mach/msm_iomap.h>
#include <mach/restart.h>
#ifdef CONFIG_ION_MSM
#include <mach/ion.h>
#endif
#include <mach/msm_memtypes.h>
#include <mach/socinfo.h>
#include <mach/board.h>
#include <mach/clk-provider.h>
#include <mach/msm_smd.h>
#include <mach/rpm-smd.h>
#include <mach/rpm-regulator-smd.h>
#include <mach/msm_smem.h>
#include <linux/msm_thermal.h>
#include "board-dt.h"
#include "clock.h"
#include "platsmp.h"
#include "spm.h"
#include "pm.h"
#include "modem_notifier.h"

//ZTE_RIL_RIL_20130615 begin
#include <linux/memblock.h>
#include <mach/boot_shared_imem_cookie.h>
//ZTE_RIL_RIL_20130615 end

#include <linux/export.h>

/*
 * Add RAM console support by ZTE_BOOT_JIA_20130121 jia.jia
 */
#ifdef CONFIG_ZTE_RAM_CONSOLE
/*
 * Set to the last 1MB region of the first 'System RAM'
 * and the region allocated by '___alloc_bootmem' should be considered
 */
#define MSM_RAM_CONSOLE_PHYS         (0x1ef00000) /* Refer to 'debug.c' in aboot */

/* add RAM console part below */
#define MSM_RAM_CONSOLE_PHYS_PART_0  (MSM_RAM_CONSOLE_PHYS)
#define MSM_RAM_CONSOLE_SIZE_PART_0  (SZ_1M)
#define MSM_RAM_CONSOLE_SIZE_TOTAL   (MSM_RAM_CONSOLE_SIZE_PART_0)
#define MSM_RAM_CONSOLE_NUM          (1)
/* add RAM console part above */

#endif /* CONFIG_ZTE_RAM_CONSOLE */
//ZTE_RIL_RIL_20130615 begin

//physical address to reserve for sdlog
#define MSM_SDLOG_PHYS      0x1F000000
#define MSM_SDLOG_SIZE      (SZ_1M * 16)
#define SDLOG_MEM_RESERVED_COOKIE    0x20130615

//ZTE_RIL_RIL_20130615 end

/*
 * Support for FTM & RECOVERY mode by ZTE_BOOT_JIA_20120305, jia.jia
 * ZTE_PLATFORM
 */

#ifdef ZTE_BOOT_MODE

static int __init bootmode_init(char *mode)
{
	int boot_mode = 0;

	if (!strncmp(mode, SOCINFO_CMDLINE_BOOTMODE_NORMAL, strlen(SOCINFO_CMDLINE_BOOTMODE_NORMAL)))
	{
		boot_mode = BOOT_MODE_NORMAL;
	}
	else if (!strncmp(mode, SOCINFO_CMDLINE_BOOTMODE_FTM, strlen(SOCINFO_CMDLINE_BOOTMODE_FTM)))
	{
		boot_mode = BOOT_MODE_FTM;
	}
	else if (!strncmp(mode, SOCINFO_CMDLINE_BOOTMODE_RECOVERY, strlen(SOCINFO_CMDLINE_BOOTMODE_RECOVERY)))
	{
		boot_mode = BOOT_MODE_RECOVERY;
	}
        else if (!strncmp(mode, SOCINFO_CMDLINE_BOOTMODE_FFBM, strlen(SOCINFO_CMDLINE_BOOTMODE_FFBM)))
        {
                boot_mode = BOOT_MODE_FFBM;
        }

	else
	{
		boot_mode = BOOT_MODE_NORMAL;
	}

	socinfo_set_boot_mode(boot_mode);

	return 0;
}

#if 0 // To fix compiling error
__setup(SOCINFO_CMDLINE_BOOTMODE, bootmode_init);
#else
static const char __setup_str_bootmode_init[] __initconst __aligned(1) = SOCINFO_CMDLINE_BOOTMODE;
static struct obs_kernel_param __setup_bootmode_init __used __section(.init.setup) __attribute__((aligned((sizeof(long))))) =
	{ SOCINFO_CMDLINE_BOOTMODE, bootmode_init, 0 };
#endif
#endif


#ifdef ZTE_BOOT_MODE

#define GPIO_VERSION1 13
#define GPIO_VERSION2 114

typedef enum {
    HW_VER_01      = 0, /* GPIO13:0 GPIO114:0 */
    HW_VER_02      = 1, /* GPIO13:0 GPIO114:1*/
    HW_VER_03      = 2, /* GPIO13:1 GPIO114:0*/
    HW_VER_MAX      = 3, /* GPIO13:1 GPIO114:1 */
    HW_VER_INVALID = 0xFF,
} zte_hw_ver_type;

#if defined(CONFIG_BOARD_WARP4)
static const char *zte_hw_ver_str[HW_VER_MAX+1] = {
    [HW_VER_01]     = "cxwA",
    [HW_VER_02]     = "cwcA",
    [HW_VER_03]     = "cwcA",
    [HW_VER_MAX]     = "cwcA",
};
#elif defined(CONFIG_MACH_GRUIS)
static const char *zte_hw_ver_str[HW_VER_MAX+1] = {
    [HW_VER_01]     = "wwuA",
    [HW_VER_02]     = "wwuA",
    [HW_VER_03]     = "wwuA",
    [HW_VER_MAX]     = "wwuA",
};
#elif defined(CONFIG_BOARD_ERIDANI)
static const char *zte_hw_ver_str[HW_VER_MAX+1] = {
    [HW_VER_01]     = "cxyB",
    [HW_VER_02]     = "cxyB",
    [HW_VER_03]     = "cxyB",
    [HW_VER_MAX]     = "cxyB",
};
#else
static const char *zte_hw_ver_str[HW_VER_MAX+1] = {
    [HW_VER_01]     = "INVALID",
    [HW_VER_02]     = "INVALID",
    [HW_VER_03]     = "INVALID",
    [HW_VER_MAX]     = "INVALID",
};
#endif

uint8_t read_zte_hw_ver_byte(void)
{
    zte_hw_ver_type hw_ver = HW_VER_INVALID;
    int32_t val_gpio = 0;
    int32_t rc = 0;
    int32_t i;
    int32_t gpio_array[] = {GPIO_VERSION1,GPIO_VERSION2};

    for(i = 0;i < sizeof(gpio_array)/sizeof(gpio_array[0]); i++)
    {
        rc =gpio_request(gpio_array[i], "hw_ver");
        if (!rc)
        {
            gpio_tlmm_config(GPIO_CFG(gpio_array[i], 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA), GPIO_CFG_ENABLE);
            rc = gpio_direction_input(gpio_array[i]);
            if (!rc)
            {
                val_gpio = gpio_get_value_cansleep(gpio_array[i]);
                hw_ver = (zte_hw_ver_type)(((hw_ver<<1) + val_gpio)& HW_VER_MAX);
            }
            else
            {
                hw_ver = HW_VER_INVALID;
                break;
            }

            gpio_free(gpio_array[i]);
        }
        else
        {
            hw_ver = HW_VER_INVALID;
            break;
        }
    }

    return hw_ver;
}
EXPORT_SYMBOL_GPL(read_zte_hw_ver_byte);

const char* read_zte_hw_ver(void)
{

  uint8_t hw_ver = read_zte_hw_ver_byte();

  if(hw_ver > HW_VER_MAX)
  {
    return (const char*)NULL;
  }
  else
  {
    return zte_hw_ver_str[hw_ver];
  }
}
#endif

static struct memtype_reserve msm8226_reserve_table[] __initdata = {
	[MEMTYPE_SMI] = {
	},
	[MEMTYPE_EBI0] = {
		.flags	=	MEMTYPE_FLAGS_1M_ALIGN,
	},
	[MEMTYPE_EBI1] = {
		.flags	=	MEMTYPE_FLAGS_1M_ALIGN,
	},
};

static int msm8226_paddr_to_memtype(unsigned int paddr)
{
	return MEMTYPE_EBI1;
}

static struct of_dev_auxdata msm8226_auxdata_lookup[] __initdata = {
	OF_DEV_AUXDATA("qcom,msm-sdcc", 0xF9824000, \
			"msm_sdcc.1", NULL),
	OF_DEV_AUXDATA("qcom,msm-sdcc", 0xF98A4000, \
			"msm_sdcc.2", NULL),
	OF_DEV_AUXDATA("qcom,msm-sdcc", 0xF9864000, \
			"msm_sdcc.3", NULL),
	OF_DEV_AUXDATA("qcom,sdhci-msm", 0xF9824900, \
			"msm_sdcc.1", NULL),
	OF_DEV_AUXDATA("qcom,sdhci-msm", 0xF98A4900, \
			"msm_sdcc.2", NULL),
	OF_DEV_AUXDATA("qcom,sdhci-msm", 0xF9864900, \
			"msm_sdcc.3", NULL),
	OF_DEV_AUXDATA("qcom,hsic-host", 0xF9A00000, "msm_hsic_host", NULL),

	{}
};

static struct reserve_info msm8226_reserve_info __initdata = {
	.memtype_reserve_table = msm8226_reserve_table,
	.paddr_to_memtype = msm8226_paddr_to_memtype,
};

static void __init msm8226_early_memory(void)
{
	reserve_info = &msm8226_reserve_info;
	of_scan_flat_dt(dt_scan_for_memory_hole, msm8226_reserve_table);
}

static void __init msm8226_reserve(void)
{
	reserve_info = &msm8226_reserve_info;
	of_scan_flat_dt(dt_scan_for_memory_reserve, msm8226_reserve_table);
	msm_reserve();
}

/*
 * Add RAM console support by ZTE_BOOT_JIA_20130121 jia.jia
 */
#ifdef CONFIG_ZTE_RAM_CONSOLE
static struct resource ram_console_resource[MSM_RAM_CONSOLE_NUM] = {
	/* add RAM console part below */
	{
		.start  = MSM_RAM_CONSOLE_PHYS_PART_0,
		.end    = MSM_RAM_CONSOLE_PHYS_PART_0 + MSM_RAM_CONSOLE_SIZE_PART_0 - 1,
		.flags	= IORESOURCE_MEM,
	},
	/* add RAM console part above */
};

static struct platform_device ram_console_device = {
	.name = "ram_console",
	.id = -1,
	.num_resources  = MSM_RAM_CONSOLE_NUM,
	.resource       = ram_console_resource,
};
#endif /* CONFIG_ZTE_RAM_CONSOLE */

/*
 * FTM device driver support
 * merged from 8960 by huang.yanjun
 */

#ifdef CONFIG_ZTE_FTM
static struct platform_device zte_ftm_device = {
    .name = "zte_ftm",
    .id = 0,
};
#endif

static struct platform_device *zte_msm8226_common_devices[] = {
	/*
   * Add RAM console support by ZTE_BOOT_JIA_20130121 jia.jia
   */
#ifdef CONFIG_ZTE_RAM_CONSOLE
	&ram_console_device,
#endif

/*merged from 8960 by huang.yanjun for FTM device driver support*/
#ifdef CONFIG_ZTE_FTM
	&zte_ftm_device
#endif
  /*
   * add other devices
   */

};

static void __init msm8226_init_buses(void)
{

	platform_add_devices(zte_msm8226_common_devices,
				ARRAY_SIZE(zte_msm8226_common_devices));
};

/*
 * Used to satisfy dependencies for devices that need to be
 * run early or in a particular order. Most likely your device doesn't fall
 * into this category, and thus the driver should not be added here. The
 * EPROBE_DEFER can satisfy most dependency problems.
 */
void __init msm8226_add_drivers(void)
{
	msm_smem_init();
	msm_init_modem_notifier_list();
	msm_smd_init();
	msm_rpm_driver_init();
	msm_spm_device_init();
	msm_pm_sleep_status_init();
	rpm_regulator_smd_driver_init();
	qpnp_regulator_init();
	if (of_board_is_rumi())
		msm_clock_init(&msm8226_rumi_clock_init_data);
	else
		msm_clock_init(&msm8226_clock_init_data);
	msm8226_init_buses();
	tsens_tm_init_driver();
	msm_thermal_device_init();
}

//ZTE_RIL_RIL_20130615 begin

static void msm_reserve_sdlog_memory(void)
{
    //reserve app memory for sdlog
    int reserver = 0;
    
    struct boot_shared_imem_cookie_type *boot_shared_imem_ptr = (struct boot_shared_imem_cookie_type *)MSM_IMEM_BASE;

    if (boot_shared_imem_ptr->app_mem_reserved == SDLOG_MEM_RESERVED_COOKIE)
    {
        pr_err("sdlog is enable, reserver 16M buffer in 0x%x \n", MSM_SDLOG_PHYS);
        reserver = memblock_reserve(MSM_SDLOG_PHYS, MSM_SDLOG_SIZE);

        if (reserver != 0)
        {
            pr_err("sdlog reserve memory failed, disable sdlog \n");
            boot_shared_imem_ptr->app_mem_reserved = 0;
        }
        
    }
    else
    {
        pr_err("sdlog is disabled \n");
    }

}

static void __init msm8226_map_io(void)
{
	msm_map_msm8226_io();
    msm_reserve_sdlog_memory();
    
}

//ZTE_RIL_RIL_20130615 end
void __init msm8226_init(void)
{
	struct of_dev_auxdata *adata = msm8226_auxdata_lookup;

	if (socinfo_init() < 0)
		pr_err("%s: socinfo_init() failed\n", __func__);

	msm8226_init_gpiomux();
	board_dt_populate(adata);
	msm8226_add_drivers();
#ifdef ZTE_BOOT_MODE
	socinfo_sync_sysfs_zte_hw_ver(read_zte_hw_ver());
#endif
}

static const char *msm8226_dt_match[] __initconst = {
	"qcom,msm8226",
	"qcom,msm8926",
	"qcom,apq8026",
	NULL
};

DT_MACHINE_START(MSM8226_DT, "Qualcomm MSM 8226 (Flattened Device Tree)")
	.map_io = msm8226_map_io,//ZTE_RIL_RIL_20130615
	.init_irq = msm_dt_init_irq,
	.init_machine = msm8226_init,
	.handle_irq = gic_handle_irq,
	.timer = &msm_dt_timer,
	.dt_compat = msm8226_dt_match,
	.reserve = msm8226_reserve,
	.init_very_early = msm8226_early_memory,
	.restart = msm_restart,
	.smp = &arm_smp_ops,
MACHINE_END
