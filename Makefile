.PHONY: clean All

All:
	@echo "----------Building project:[ bootloader - Debug ]----------"
	@cd "bootloader" && "$(MAKE)" -f  "bootloader.mk" PreBuild && "$(MAKE)" -f  "bootloader.mk" && "$(MAKE)" -f  "bootloader.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ bootloader - Debug ]----------"
	@cd "bootloader" && "$(MAKE)" -f  "bootloader.mk" clean
