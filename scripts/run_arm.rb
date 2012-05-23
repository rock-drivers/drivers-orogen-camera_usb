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
    camera.brightness = 133
    camera.contrast = 5
    camera.saturation = 83
    camera.sharpness = 25
    camera.backlight_compensation = 0
    camera.power_line_frequency = "disabled"
    camera.fps = 10

    camera.focus_mode = "auto"
    camera.focus = 0
    camera.horizontal_flip = 0
    camera.vertical_flip = 0
    camera.zoom = 10
    camera.single_auto_focus = 0
    camera.focus_overlay = 0
    camera.effects = 0
    camera.focus_complete = 0
    camera.test_pattern = 0

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
