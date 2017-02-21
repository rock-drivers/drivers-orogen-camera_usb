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
    
    camera.camera_format = :MODE_RGB
    camera.output_format = :MODE_JPEG
    camera.width = 640
    camera.height = 480
    
    camera.grab_mode = :SingleFrame

    camera.configure
    camera.start

   Vizkit.display camera.frame
   Vizkit.exec

    STDERR.puts "shutting down"
end
