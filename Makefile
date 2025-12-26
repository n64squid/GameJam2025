V=1
GAME=gamejam2025
SOURCE_DIR=src
BUILD_DIR=build
FILESYSTEM_DIR=filesystem
IMAGE_DIR=assets/images
FONTS_DIR=assets/fonts
AUDIO_DIR=assets/audio
MODELS_DIR=assets/models

# Images
ASEPRITE_FILES=$(wildcard $(IMAGE_DIR)/*.ase)
ASEPRITE_PNGS=$(ASEPRITE_FILES:.ase=.png)

IMAGE_FILESYSTEM=$(FILESYSTEM_DIR)/images
IMAGE_FILES=$(wildcard $(IMAGE_DIR)/*.png) $(wildcard $(IMAGE_DIR)/*/*.png) $(ASEPRITE_PNGS)
IMAGE_SPRITES=$(sort $(subst assets,filesystem,$(IMAGE_FILES:.png=.sprite)))

# Fonts
FONTS_FILESYSTEM=$(FILESYSTEM_DIR)/fonts
FONTS_FILES=$(wildcard $(FONTS_DIR)/*.ttf)
FONTS_FONTS64=$(subst assets,filesystem,$(FONTS_FILES:.ttf=.font64))

# Audio
AUDIO_FILESYSTEM=$(FILESYSTEM_DIR)/audio
AUDIO_WAV_FILES=$(wildcard $(AUDIO_DIR)/*.wav)
AUDIO_WAV_WAV64=$(subst assets,filesystem,$(AUDIO_WAV_FILES:.wav=.wav64))
AUDIO_MP3_FILES=$(wildcard $(AUDIO_DIR)/*.mp3)
AUDIO_MP3_WAV64=$(subst assets,filesystem,$(AUDIO_MP3_FILES:.mp3=.wav64))

# Models
MODELS_FILESYSTEM=$(FILESYSTEM_DIR)/models
MODELS_FILES=$(wildcard $(MODELS_DIR)/*.blend)
MODELS_GLTF=$(MODELS_FILES:.blend=.gltf)
MODELS_MODEL64=$(subst assets,filesystem,$(MODELS_FILES:.blend=.model64))

MODELS_IMAGE= $(wildcard $(MODELS_DIR)/*png)
MODELS_SPRITES=$(sort $(subst assets,filesystem,$(MODELS_IMAGE:.png=.sprite)))

MKFONT_FLAGS=--outline 1

include $(N64_INST)/include/n64.mk

all: $(GAME).z64
.PHONY: all

OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(subst .c,.o,$(wildcard $(SOURCE_DIR)/*.c))))

# Rules for sprites
$(IMAGE_FILESYSTEM)/%.sprite: $(IMAGE_DIR)/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o $(dir $@) $<

# Rules for audio
AVANTO_AUDIOCONV_FLAGS += --wav-mono  --wav-resample 22050
$(AUDIO_FILESYSTEM)/%.wav64: $(AUDIO_DIR)/%.mp3
	@mkdir -p $(dir $@)
	@echo "    [MP3 SFX] $@"
	$(N64_AUDIOCONV) $(AVANTO_AUDIOCONV_FLAGS) -o $(dir $@) "$<"


$(AUDIO_FILESYSTEM)/%.wav64: $(AUDIO_DIR)/%.wav
	@mkdir -p $(dir $@)
	@echo "    [MP3 SFX] $@"
	$(N64_AUDIOCONV) $(AVANTO_AUDIOCONV_FLAGS) -o $(dir $@) "$<"

# Rules for 3D models
$(MODELS_FILESYSTEM)/%.sprite: $(MODELS_DIR)/%.png
	@mkdir -p $(dir $@)
	@echo "    [MODEL_SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o $(dir $@) $<

# Rules for Aseprite -> PNG
$(ASEPRITE_PNGS): $(ASEPRITE_FILES)
	@echo "    [ASEPRITE] $(patsubst %.png,%.ase,$@) $(notdir $@)"
	cd $(dir $@) && aseprite $(notdir $(patsubst %.png,%.ase,$@)) -b --sheet $(notdir $@) > /dev/null

# Rules for fonts
$(FONTS_FILESYSTEM)/%.font64: $(FONTS_DIR)/%.ttf
	@echo "    [FONT] $@"
	@mkdir -p $(dir $@)
	$(N64_MKFONT) $(MKFONT_FLAGS) -o $(FONTS_FILESYSTEM) "$<"

# Rules for models
$(MODELS_DIR)/%.gltf: $(MODELS_DIR)/%.blend
	@echo "    [BLENDER] $@"
	@mkdir -p $(dir $@)
	blender -b "$(patsubst %.gltf,%.blend,$@)" --python-expr "import bpy; bpy.ops.export_scene.gltf(filepath='$@', export_format='GLTF_SEPARATE')"

$(MODELS_FILESYSTEM)/%.model64: $(MODELS_DIR)/%.gltf
	@mkdir -p $(dir $@)
	@echo "    [MODEL] $@"
	$(N64_MKMODEL) -o $(MODELS_FILESYSTEM) "$<"

PAD_ROM: $(GAME).z64
	@echo "    [$@]"
	@file=$<; \
	if [ -f "$$file" ]; then \
	  size=$$(stat -c%s "$$file"); \
	  size_mb=$$(( (size + 1048575) / 1048576 )); \
	  target_mb=4; \
	  while [ $$target_mb -lt $$size_mb ]; do \
	    target_mb=$$(( $$target_mb * 2 )); \
	  done; \
	  target_bytes=$$(( $$target_mb * 1048576 )); \
	  echo "Padding $$file from $$size bytes to $$target_bytes bytes ($$target_mb MB)"; \
	  truncate -s $$target_bytes "$$file"; \
	else \
	  echo "File $$file does not exist."; \
	fi

GEN_CRC: $(GAME).z64
	@echo "    [$@]"
	n64crc $<


# Complete compiling
$(IMAGE_FILESYSTEM): $(ASEPRITE_PNGS) $(IMAGE_SPRITES)
$(FONTS_FILESYSTEM): $(FONTS_FONTS64)
$(AUDIO_FILESYSTEM): $(AUDIO_MP3_WAV64) $(AUDIO_WAV_WAV64)
$(MODELS_FILESYSTEM): $(MODELS_SPRITES) $(MODELS_MODEL64)
$(BUILD_DIR)/$(GAME).dfs: $(FONTS_FILESYSTEM) $(MODELS_FILESYSTEM) $(IMAGE_FILESYSTEM) $(AUDIO_FILESYSTEM)
$(BUILD_DIR)/$(GAME).elf: $(OBJS)

$(GAME).z64: N64_ROM_TITLE="Game Jam 2025"
$(GAME).z64: $(BUILD_DIR)/$(GAME).dfs

# Cleaning
clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(GAME).z64
	rm -rf $(FILESYSTEM_DIR)
	rm -f $(ASEPRITE_PNGS) $(MODELS_GLTF)
	rm -f $(MODELS_DIR)/*.bin
.PHONY: clean

test:
	@echo "Images" $(IMAGE_FILES)
.PHONY: test

-include $(wildcard $(BUILD_DIR)/*.d)
