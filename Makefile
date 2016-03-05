.PHONY: clean All

All:
	@echo "----------Building project:[ kernel - Debug ]----------"
	@cd "kernel" && "$(MAKE)" -f  "kernel.mk" PreBuild && "$(MAKE)" -f  "kernel.mk" && "$(MAKE)" -f  "kernel.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ kernel - Debug ]----------"
	@cd "kernel" && "$(MAKE)" -f  "kernel.mk" clean
