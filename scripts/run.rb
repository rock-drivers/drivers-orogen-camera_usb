#! /usr/bin/env ruby
# -*- coding: utf-8 -*-
# If you want to start the Microsoft Life Cam or the Gumstix camera e-CAM32
# you should use the corresponding ruby run-script. 

require 'orocos'
require 'vizkit'
include Orocos
Orocos.initialize

Orocos.run 'camera_usb_deployment' do
    camera = TaskContext.get 'camera_usb_deployment'  
  
    camera.camera_device = "/dev/video0"
    camera.brightness = 133
    camera.contrast = 5
    camera.saturation = 83
    camera.sharpness = 25
    camera.backlight_compensation = 0
    camera.power_line_frequency = "disabled"

    camera.fps = 20

    # focus mode: manual or auto
    # focus value: 0 = invinite, 40 = close objects
    camera.focus_mode = "auto"
    camera.focus = 0
    camera.horizontal_flip = 0
    camera.vertical_flip = 0
    camera.zoom = 10

    camera.camera_format = :MODE_JPEG # Not used, alwas set to MODE_JPEG.
    camera.width = 640
    camera.height = 480

    camera.configure
    camera.start

   Vizkit.display camera.frame
   Vizkit.exec
   #while true
   #	sleep 1
   #end

    STDERR.puts "shutting down"
end
