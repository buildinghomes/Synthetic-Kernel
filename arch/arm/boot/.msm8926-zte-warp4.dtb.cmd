cmd_arch/arm/boot/msm8926-zte-warp4.dtb := /home/dankmemes/android/Synthetic-Kernel/scripts/dtc/dtc -O dtb -o arch/arm/boot/msm8926-zte-warp4.dtb -b 0  -d arch/arm/boot/.msm8926-zte-warp4.dtb.d arch/arm/boot/dts/msm8926-zte-warp4.dts

source_arch/arm/boot/msm8926-zte-warp4.dtb := arch/arm/boot/dts/msm8926-zte-warp4.dts

deps_arch/arm/boot/msm8926-zte-warp4.dtb := \
  arch/arm/boot/dts/msm8926.dtsi \
  arch/arm/boot/dts/msm8226.dtsi \
  arch/arm/boot/dts/skeleton.dtsi \
  arch/arm/boot/dts/msm8226-ion.dtsi \
  arch/arm/boot/dts/msm8226-camera.dtsi \
  arch/arm/boot/dts/msm-gdsc.dtsi \
  arch/arm/boot/dts/msm8226-iommu.dtsi \
  arch/arm/boot/dts/msm-iommu-v1.dtsi \
  arch/arm/boot/dts/msm8226-smp2p.dtsi \
  arch/arm/boot/dts/msm8226-gpu.dtsi \
  arch/arm/boot/dts/msm8226-bus.dtsi \
  arch/arm/boot/dts/msm8226-mdss.dtsi \
  arch/arm/boot/dts/msm8226-mdss-panels.dtsi \
  arch/arm/boot/dts/dsi-panel-hx8394a-720p-video.dtsi \
  arch/arm/boot/dts/dsi-panel-nt35590-720p-video.dtsi \
  arch/arm/boot/dts/dsi-panel-nt35521-720p-video.dtsi \
  arch/arm/boot/dts/dsi-panel-nt35596-1080p-video.dtsi \
  arch/arm/boot/dts/dsi-panel-nt35590-720p-cmd.dtsi \
  arch/arm/boot/dts/dsi-panel-ssd2080m-720p-video.dtsi \
  arch/arm/boot/dts/dsi-panel-jdi-1080p-video.dtsi \
  arch/arm/boot/dts/msm8226-coresight.dtsi \
  arch/arm/boot/dts/msm8226-iommu-domains.dtsi \
  arch/arm/boot/dts/msm-rdbg.dtsi \
  arch/arm/boot/dts/msm-pm8226-rpm-regulator.dtsi \
  arch/arm/boot/dts/msm-pm8226.dtsi \
  arch/arm/boot/dts/msm8226-regulator.dtsi \
  arch/arm/boot/dts/msm8226-v2-pm.dtsi \
  arch/arm/boot/dts/msm8226-720p-mtp.dtsi \
  arch/arm/boot/dts/msm8226-camera-sensor-mtp.dtsi \
  arch/arm/boot/dts/batterydata-palladium.dtsi \
  arch/arm/boot/dts/batterydata-mtp-3000mah.dtsi \
  arch/arm/boot/dts/msm8226-camera-sensor-mtp.dtsi \
  arch/arm/boot/dts/msm8926-zte-warp4.dtsi \
  arch/arm/boot/dts/touch-key-backlight_warp4.dtsi \
  arch/arm/boot/dts/msm8226-camera-sensor-zte.dtsi \
  arch/arm/boot/dts/dsi-panel-zte-lead-hsd-otm9608-qhd-video.dtsi \
  arch/arm/boot/dts/dsi-panel-zte-yushun-lg-nt35516-qhd-video.dtsi \
  arch/arm/boot/dts/dsi-panel-zte-lead-hx8394d-boe-5p0-720p-video.dtsi \
  arch/arm/boot/dts/dsi-panel-zte-yushun-nt35521-lg-5p0-720p-video.dtsi \

arch/arm/boot/msm8926-zte-warp4.dtb: $(deps_arch/arm/boot/msm8926-zte-warp4.dtb)

$(deps_arch/arm/boot/msm8926-zte-warp4.dtb):
