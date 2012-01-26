#! /usr/bin/env ruby
# -*- coding: utf-8 -*-

require 'orocos'
include Orocos
Orocos.initialize

Orocos.run 'camera_usb_deployment' , :wait => 60 do 
    camera = TaskContext.get 'camera_usb_deployment'  

    camera.camera_device = '/dev/video1'
    camera.brightness = 133
    camera.contrast = 5
    camera.saturation = 83
    camera.sharpness = 25
    camera.backlight_compensation = 0
    camera.power_line_frequency = "disabled"
    camera.fps = 10

    camera.camera_format = :MODE_JPEG # Not used, alwas set to MODE_JPEG.
    camera.width = 1280
    camera.height = 720

    camera.configure
    camera.start

    while true
        sleep 0.01
    end

    STDERR.puts "shutting down"
end
