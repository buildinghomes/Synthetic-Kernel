cmd_arch/arm/boot/msm8226-v2-1080p-cdp.dtb := /home/dankmemes/android/Synthetic-Kernel/scripts/dtc/dtc -O dtb -o arch/arm/boot/msm8226-v2-1080p-cdp.dtb -b 0  -d arch/arm/boot/.msm8226-v2-1080p-cdp.dtb.d arch/arm/boot/dts/msm8226-v2-1080p-cdp.dts

source_arch/arm/boot/msm8226-v2-1080p-cdp.dtb := arch/arm/boot/dts/msm8226-v2-1080p-cdp.dts

deps_arch/arm/boot/msm8226-v2-1080p-cdp.dtb := \
  arch/arm/boot/dts/msm8226-v2.dtsi \
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
  arch/arm/boot/dts/msm8226-1080p-cdp.dtsi \
  arch/arm/boot/dts/msm8226-camera-sensor-cdp.dtsi \
  arch/arm/boot/dts/msm8226-camera-sensor-cdp.dtsi \

arch/arm/boot/msm8226-v2-1080p-cdp.dtb: $(deps_arch/arm/boot/msm8226-v2-1080p-cdp.dtb)

$(deps_arch/arm/boot/msm8226-v2-1080p-cdp.dtb):
