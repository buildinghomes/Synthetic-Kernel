cmd_arch/arm/boot/msm8926-zte-rf360.dtb := /home/dankmemes/android/Synthetic-Kernel/scripts/dtc/dtc -O dtb -o arch/arm/boot/msm8926-zte-rf360.dtb -b 0  -d arch/arm/boot/.msm8926-zte-rf360.dtb.d arch/arm/boot/dts/msm8926-zte-rf360.dts

source_arch/arm/boot/msm8926-zte-rf360.dtb := arch/arm/boot/dts/msm8926-zte-rf360.dts

deps_arch/arm/boot/msm8926-zte-rf360.dtb := \
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
  arch/arm/boot/dts/msm8926-zte-rf360.dtsi \
  arch/arm/boot/dts/touch-key-backlight_rf360.dtsi \
  arch/arm/boot/dts/dsi-panel-orise1283a-boe-5p7-720p-video-zte-100.dtsi \
  arch/arm/boot/dts/dsi-panel-orise1283a-cpt-5p7-720p-video-zte-101.dtsi \
  arch/arm/boot/dts/dsi-panel-orise1283a-auo-5p7-720p-video-zte-103.dtsi \

arch/arm/boot/msm8926-zte-rf360.dtb: $(deps_arch/arm/boot/msm8926-zte-rf360.dtb)

$(deps_arch/arm/boot/msm8926-zte-rf360.dtb):
