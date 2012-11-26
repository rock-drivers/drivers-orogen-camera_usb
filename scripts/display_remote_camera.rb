#! /usr/bin/env ruby
# -*- coding: utf-8 -*-

require 'orocos'
require 'vizkit'
include Orocos
Orocos::CORBA.call_timeout = 40000
Orocos::CORBA.connect_timeout = 10000

# Overrides default corba nameserver
Orocos::CORBA.name_service.ip = "10.250.8.21" 

# uses default- and addtional corba nameserver
#Orocos::name_service << Orocos::CORBA::NameService.new("10.250.8.21")
Orocos.initialize

camera = TaskContext.get 'payloaditem_3_cam_emi'  

frame_reader = camera.frame.reader

#while(true)
#    sample = frame_reader.read
#
#    if sample
#        puts "Frame: #{sample.image.size}"
#    end
#end

Vizkit.display camera.frame
Vizkit.exec

