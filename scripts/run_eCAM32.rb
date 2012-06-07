#! /usr/bin/env ruby
# -*- coding: utf-8 -*-

require 'orocos'
include Orocos
Orocos.initialize

Orocos.run 'camera_usb_deployment' , :wait => 60 do 
    camera = TaskContext.get 'camera_usb_deployment'  

    # Using fix udev symlinks on the gumstix.	
    # gumstix camera: /dev/omap_camera, microsoft web cam: /dev/microsoft_life_cam
    camera.camera_device = '/dev/omap_camera'
    camera.brightness = 0 # -48 to 48 (step 1), default: 0
    camera.contrast = 5 # -12 to 12 (step 1), default: 0
    camera.saturation = 0 # -48 to 48 (step 1), default: 0
    camera.sharpness = 0 # -40 to 40 (step 1), default: 0
    camera.fps = 10

    camera.focus_mode = "auto" # 0 to 1 (step 1), default: 0
    camera.focus = 0 # 0 to 1023 (step 1), default: 0
    camera.horizontal_flip = 0 # 0 to 1 (step 1), default: 0
    camera.vertical_flip = 0 # 0 to 1 (step 1), default: 0
    camera.single_auto_focus = 0 # 0 to 1 (step 1), default: 0
    camera.focus_overlay = 1 # 0 to 1 (step 1), default: 0
    camera.effects = 0 # 0 to 7 (step 1), default: 0
    camera.focus_complete = 0 # 0 to 1 (step 1), default: 0
    camera.test_pattern = 1 # 0 to 1 (step 1), default: 1

    camera.camera_format = :MODE_JPEG # Not used, alwas set to MODE_JPEG.
    camera.width = 640	
    camera.height = 480

    camera.configure
    camera.start

    while true
        sleep 0.1
    end

    STDERR.puts "shutting down"
end
