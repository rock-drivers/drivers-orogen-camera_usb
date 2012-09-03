#! /usr/bin/env ruby
# -*- coding: utf-8 -*-
# If you don't use this script on a gumstix, you have to change the video-device (e.g. to /dev/video0)

require 'orocos'
require 'vizkit'
include Orocos
Orocos.initialize

Orocos.run 'camera_usb_deployment' do
    camera = TaskContext.get 'camera_usb_deployment'  
  
    camera.camera_device = "/dev/video0"
    camera.brightness = 133 # 30 to 255 (step 1), default: 133
    camera.contrast = 5 # 0 to 10 (step 1), default: 5 
    camera.saturation = 83 # 0 to 200 (step 1), default: 83    
    camera.power_line_frequency = "disabled" # disabled, 50Hz, 60Hz, none
    camera.sharpness = 25 # 0 to 50 (step 1), default: 25 
    camera.backlight_compensation = 0 # 0 to 10 (step 1), default: 0,
    camera.focus_mode = "auto" # auto, manual 
    camera.focus = 0 # 0 to 40 (step 1), default: 0
    camera.zoom = 0 # 0 to 10 (step 1), default: 0

    camera.fps = 20

    camera.camera_format = :MODE_JPEG # Not used, alwas set to MODE_JPEG.
    camera.width = 640
    camera.height = 480

    camera.configure
    camera.start

   Vizkit.display camera#.frame
   Vizkit.exec
   #while true
   #	sleep 1
   #end

    STDERR.puts "shutting down"
end
