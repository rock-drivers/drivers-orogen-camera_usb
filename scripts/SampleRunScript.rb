#! /usr/bin/env ruby
# -*- coding: utf-8 -*-

require 'orocos'
include Orocos
Orocos.initialize

# setup the environment so that ruby can find the test deployment
# ENV['PKG_CONFIG_PATH'] = "/home/neo/Desktop/orogen_camera_usb/build:#{File.expand_path("..", File.dirname(__FILE__))}/build:#{ENV['PKG_CONFIG_PATH']}"

Orocos.run 'camera_usb_test' do
    camera = TaskContext.get 'CameraTask'  

    #  Orocos.log_all_ports


    sleep 1

    camera.grab_mode = :Continuously
    camera.configure
    camera.start
    sleep 1

    #viewer = TaskContext.get 'camera_viewer'
    #viewer.frame.connect_to camera.frame

    #viewer.start

    for i in (1..1000000)
        sleep 0.01
    end 

    STDERR.puts "shutting down"
end
