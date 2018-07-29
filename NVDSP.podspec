Pod::Spec.new do |s|
  s.name           = 'NVDSP'
  s.version        = '0.0.2'
  s.summary        = 'High-performance DSP for audio on iOS and OSX with Novocaine.'
  s.license        = { :type => 'MIT', :file => 'license.txt' }
  s.homepage       = 'https://github.com/Vinrobot/NVDSP'
  s.authors        = {'Bart Olsthoorn' => 'bartolsthoorn@gmail.com'}
  s.source         = { :git => 'https://github.com/Vinrobot/NVDSP.git', :tag => "#{s.version}" }
  s.source_files   = '*.{h,mm}', 'Filters', 'Utilities'
  s.source_files   = "NVDSP", "NVDSP/**/*.{h,m,mm}"
  s.public_header_files = "NVDSP/**/*.h"
  s.platform       = :ios
end
