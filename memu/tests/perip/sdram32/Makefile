ROOT := ../../..
BUILD := ../build/sdram32
RTL := $(ROOT)/vsrc/perip/sdram

.PHONY: test clean

test:
	verilator --binary --timing -Wno-fatal --top-module sdram32_tb \
		--Mdir $(BUILD) \
		sdram32_tb.v $(RTL)/sdram_top_apb.v \
		$(RTL)/core_sdram_axi4/sdram_axi_core.v $(RTL)/sdram.v
	$(BUILD)/Vsdram32_tb

clean:
	rm -rf $(BUILD)
