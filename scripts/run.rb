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
    
    # Unset parameters which belong to the camera_usb module will be ignored now.
=begin
    camera.brightness = 128
    camera.contrast = 128
    camera.saturation = 128
    camera.sharpness = 25
    camera.backlight_compensation = 0
    camera.power_line_frequency = "disabled"
    camera.fps = 20
    # focus mode: manual or auto
    # focus value: 0 = invinite, 40 = close objects
    camera.exposure_mode = "auto"
    camera.exposure = 1000
    camera.gain_mode_auto = true
    camera.gain = 100
    camera.horizontal_flip = 0
    camera.vertical_flip = 0
    camera.zoom = 0
=end

    camera.camera_format = :MODE_JPEG # Not used, alwas set to MODE_JPEG.
    camera.width = 1280
    camera.height = 768
    camera.focus_mode = "manual"
    camera.focus = 0

    camera.configure
    camera.start

   Vizkit.display camera.frame
   Vizkit.exec
   #while true
   #	sleep 1
   #end

    STDERR.puts "shutting down"
end
