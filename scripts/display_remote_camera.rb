#! /usr/bin/env ruby
# -*- coding: utf-8 -*-

require 'orocos'
require 'vizkit'
include Orocos
Nameservice::enable(:CORBA, :host => "10.250.3.216")
Orocos.initialize

camera = TaskContext.get 'camera_usb_deployment'  

Vizkit.display camera.frame
Vizkit.exec

