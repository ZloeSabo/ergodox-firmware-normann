currentPath = $(shell pwd)
qmkPath = qmk_firmware
firmwareBuildPath = $(qmkPath)/keyboards/ergodox_ez/keymaps/zloesabo
releaseFile = ergodox_ez_zloesabo.hex
releaseTargetPath = release
makeTarget = ergodox_ez:zloesabo
firmwareFiles = config.h keymap.c rules.mk
firmwareTargetFiles = $(addprefix $(firmwareBuildPath)/, $(firmwareFiles))

.PHONY: build
build: \
	repository \
	container \
	copy_firmware \
	compile \
	copy_release

.PHONY: repository
repository: ${qmkPath}

.PHONY: container
container:
	docker pull qmkfm/base_container:latest

copy_firmware: repository $(firmwareBuildPath) $(firmwareTargetFiles)

copy_release: repository compile ${releaseTargetPath} release/${releaseFile}

compile: copy_firmware container
	docker run --rm -it \
		-w /qmk_firmware \
		-v "$(currentPath)/$(qmkPath)":/qmk_firmware \
		qmkfm/base_container \
		make $(makeTarget)

.PHONY: clean
clean:
	rm -rf "$(qmkPath)" "$(releaseTargetPath)"

.PHONY: clean_firmware_path
clean_firmware_path:
	rm -rf "$(firmwareBuildPath)/*"

${qmkPath}:
	git clone --depth 1 --recurse-submodules --shallow-submodules -j 8 https://github.com/qmk/qmk_firmware.git "$(qmkPath)"

${firmwareBuildPath}: $(qmkPath)
	mkdir -p "$(firmwareBuildPath)"

${releaseTargetPath}:
	mkdir $(releaseTargetPath)

# Copies the new release to the release folder only when the build result changes
release/${releaseFile}: ${qmkPath}/${releaseFile}
	cp -f $? $@

# Any file in the build path depends on corresponding file changes in the current directory
${firmwareBuildPath}/%: % ${firmwareBuildPath}
	cp $* $@

${qmkPath}/${releaseFile}: compile