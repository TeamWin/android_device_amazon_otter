/*
   Copyright (c) 2015, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fs.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#define ORIGINAL_DATA_PARTITION "/dev/block/mmcblk0p10"
#define SIZE_THRESHOLD 2048

void vendor_load_properties() {
	unsigned int block_device_size;
	int fd, ret;

	fd = open(ORIGINAL_DATA_PARTITION, O_RDONLY);
	if (fd < 0) {
		ERROR("libinit_otter: failed to open '%s'\n", ORIGINAL_DATA_PARTITION);
		return;
	}
	ret = ioctl(fd, BLKGETSIZE, &block_device_size);
	close(fd);
	if (ret) {
		ERROR("libinit_otter: ioctl error\n");
		return;
	}
	ERROR("libinit_otter: '%s' size is %u\n", ORIGINAL_DATA_PARTITION, block_device_size);
	if (block_device_size > SIZE_THRESHOLD) {
		// This is a regular otter
		ERROR("libinit_otter: applying otter\n");
		property_set("ro.product.device", "otter");
		property_set("ro.build.product", "otter");
		rename("/etc/twrp.fstab.otter", "/etc/twrp.fstab");
	} else {
		// This is otterx
		ERROR("libinit_otter: applying otterx\n");
                property_set("ro.product.device", "otterx");
                property_set("ro.build.product", "otterx");
		rename("/etc/twrp.fstab.otterx", "/etc/twrp.fstab");
	}
}
