#! /usr/bin/env ruby
# -*- coding: utf-8 -*-

require 'orocos'
require 'readline' 
require 'jpeg_conversion'

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
    camera.fps = 10

    camera.camera_format = :MODE_JPEG # Not used, alwas set to MODE_JPEG.
    camera.width = 640 #1280
    camera.height = 480 # 720

    camera.configure
    camera.start

    frame_reader = camera.frame.reader
    counter = 0
    conversion = Conversion::JpegConversion.new

    while true

        frame = frame_reader.read
        if frame
            puts "Store test_frame_#{counter}"
            conversion::store_frame("test_frame_#{counter}", frame)
            counter = counter + 1
        end
        sleep 2 
    end

    Readline::readline("Press ENTER to exit")
    STDERR.puts "shutting down"
end
