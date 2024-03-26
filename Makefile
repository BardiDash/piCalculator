.PHONY: clean All

All:
	@echo "----------Building project:[ PiMultiThread - Debug ]----------"
	@cd "PiMultiThread" && "$(MAKE)" -f  "PiMultiThread.mk"
clean:
	@echo "----------Cleaning project:[ PiMultiThread - Debug ]----------"
	@cd "PiMultiThread" && "$(MAKE)" -f  "PiMultiThread.mk" clean
