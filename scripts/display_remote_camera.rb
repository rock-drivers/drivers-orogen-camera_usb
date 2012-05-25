#! /usr/bin/env ruby
# -*- coding: utf-8 -*-

require 'orocos'
require 'vizkit'
include Orocos
Nameservice::enable(:CORBA, :host => "192.168.111.60")
Orocos.initialize

camera = TaskContext.get 'camera_usb_deployment'  

Vizkit.display camera.frame
Vizkit.exec

