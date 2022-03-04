#ifndef __INTEL_CPUID_H__
 #define __INTEL_CPUID_H__
  
 #define CPUID_SIGNATURE                         0x00
  
 #define CPUID_SIGNATURE_GENUINE_INTEL_EBX  SIGNATURE_32 ('G', 'e', 'n', 'u')
 #define CPUID_SIGNATURE_GENUINE_INTEL_EDX  SIGNATURE_32 ('i', 'n', 'e', 'I')
 #define CPUID_SIGNATURE_GENUINE_INTEL_ECX  SIGNATURE_32 ('n', 't', 'e', 'l')
  
  
 #define CPUID_VERSION_INFO                      0x01
  
 typedef union {
   struct {
     UINT32  SteppingId:4;        
     UINT32  Model:4;             
     UINT32  FamilyId:4;          
     UINT32  ProcessorType:2;     
     UINT32  Reserved1:2;         
     UINT32  ExtendedModelId:4;   
     UINT32  ExtendedFamilyId:8;  
     UINT32  Reserved2:4;         
   } Bits;
   UINT32    Uint32;
 } CPUID_VERSION_INFO_EAX;
  
 #define CPUID_VERSION_INFO_EAX_PROCESSOR_TYPE_ORIGINAL_OEM_PROCESSOR     0x00
 #define CPUID_VERSION_INFO_EAX_PROCESSOR_TYPE_INTEL_OVERDRIVE_PROCESSOR  0x01
 #define CPUID_VERSION_INFO_EAX_PROCESSOR_TYPE_DUAL_PROCESSOR             0x02
  
 typedef union {
   struct {
     UINT32  BrandIndex:8;
     UINT32  CacheLineSize:8;
     UINT32  MaximumAddressableIdsForLogicalProcessors:8;
     UINT32  InitialLocalApicId:8;
   } Bits;
   UINT32    Uint32;
 } CPUID_VERSION_INFO_EBX;
  
 typedef union {
   struct {
     UINT32  SSE3:1;
     UINT32  PCLMULQDQ:1;
     UINT32  DTES64:1;
     UINT32  MONITOR:1;
     UINT32  DS_CPL:1;
     UINT32  VMX:1;
     UINT32  SMX:1;
     UINT32  EIST:1;
     UINT32  TM2:1;
     UINT32  SSSE3:1;
     UINT32  CNXT_ID:1;
     UINT32  SDBG:1;
     UINT32  FMA:1;
     UINT32  CMPXCHG16B:1;
     UINT32  xTPR_Update_Control:1;
     UINT32  PDCM:1;
     UINT32  Reserved:1;
     UINT32  PCID:1;
     UINT32  DCA:1;
     UINT32  SSE4_1:1;
     UINT32  SSE4_2:1;
     UINT32  x2APIC:1;
     UINT32  MOVBE:1;
     UINT32  POPCNT:1;
     UINT32  TSC_Deadline:1;
     UINT32  AESNI:1;
     UINT32  XSAVE:1;
     UINT32  OSXSAVE:1;
     UINT32  AVX:1;
     UINT32  F16C:1;
     UINT32  RDRAND:1;
     UINT32  NotUsed:1;
   } Bits;
   UINT32    Uint32;
 } CPUID_VERSION_INFO_ECX;
  
 typedef union {
   struct {
     UINT32  FPU:1;
     UINT32  VME:1;
     UINT32  DE:1;
     UINT32  PSE:1;
     UINT32  TSC:1;
     UINT32  MSR:1;
     UINT32  PAE:1;
     UINT32  MCE:1;
     UINT32  CX8:1;
     UINT32  APIC:1;
     UINT32  Reserved1:1;
     UINT32  SEP:1;
     UINT32  MTRR:1;
     UINT32  PGE:1;
     UINT32  MCA:1;
     UINT32  CMOV:1;
     UINT32  PAT:1;
     UINT32  PSE_36:1;
     UINT32  PSN:1;
     UINT32  CLFSH:1;
     UINT32  Reserved2:1;
     UINT32  DS:1;
     UINT32  ACPI:1;
     UINT32  MMX:1;
     UINT32  FXSR:1;
     UINT32  SSE:1;
     UINT32  SSE2:1;
     UINT32  SS:1;
     UINT32  HTT:1;
     UINT32  TM:1;
     UINT32  Reserved3:1;
     UINT32  PBE:1;
   } Bits;
   UINT32    Uint32;
 } CPUID_VERSION_INFO_EDX;
  
  
 #define CPUID_CACHE_INFO                        0x02
  
 typedef union {
   struct {
     UINT32  Reserved:31;
     UINT32  NotValid:1;
   } Bits;
   UINT8   CacheDescriptor[4];
   UINT32  Uint32;
 } CPUID_CACHE_INFO_CACHE_TLB;
  
  
 #define CPUID_SERIAL_NUMBER                     0x03
  
  
 #define CPUID_CACHE_PARAMS                      0x04
  
 typedef union {
   struct {
     UINT32  CacheType:5;
     UINT32  CacheLevel:3;
     UINT32  SelfInitializingCache:1;
     UINT32  FullyAssociativeCache:1;
     UINT32  Reserved:4;
     UINT32  MaximumAddressableIdsForLogicalProcessors:12;
     UINT32  MaximumAddressableIdsForProcessorCores:6;
   } Bits;
   UINT32  Uint32;
 } CPUID_CACHE_PARAMS_EAX;
  
 #define CPUID_CACHE_PARAMS_CACHE_TYPE_NULL         0x00
 #define CPUID_CACHE_PARAMS_CACHE_TYPE_DATA         0x01
 #define CPUID_CACHE_PARAMS_CACHE_TYPE_INSTRUCTION  0x02
 #define CPUID_CACHE_PARAMS_CACHE_TYPE_UNIFIED      0x03
  
 typedef union {
   struct {
     UINT32  LineSize:12;
     UINT32  LinePartitions:10;
     UINT32  Ways:10;
   } Bits;
   UINT32  Uint32;
 } CPUID_CACHE_PARAMS_EBX;
  
 typedef union {
   struct {
     UINT32  Invalidate:1;
     UINT32  CacheInclusiveness:1;
     UINT32  ComplexCacheIndexing:1;
     UINT32  Reserved:29;
   } Bits;
   UINT32  Uint32;
 } CPUID_CACHE_PARAMS_EDX;
  
  
 #define CPUID_MONITOR_MWAIT                     0x05
  
 typedef union {
   struct {
     UINT32  SmallestMonitorLineSize:16;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_MONITOR_MWAIT_EAX;
  
 typedef union {
   struct {
     UINT32  LargestMonitorLineSize:16;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_MONITOR_MWAIT_EBX;
  
 typedef union {
   struct {
     UINT32  ExtensionsSupported:1;
     UINT32  InterruptAsBreak:1;
     UINT32  Reserved:30;
   } Bits;
   UINT32  Uint32;
 } CPUID_MONITOR_MWAIT_ECX;
  
 typedef union {
   struct {
     UINT32  C0States:4;
     UINT32  C1States:4;
     UINT32  C2States:4;
     UINT32  C3States:4;
     UINT32  C4States:4;
     UINT32  C5States:4;
     UINT32  C6States:4;
     UINT32  C7States:4;
   } Bits;
   UINT32  Uint32;
 } CPUID_MONITOR_MWAIT_EDX;
  
  
 #define CPUID_THERMAL_POWER_MANAGEMENT          0x06
  
 typedef union {
   struct {
     UINT32  DigitalTemperatureSensor:1;
     UINT32  TurboBoostTechnology:1;
     UINT32  ARAT:1;
     UINT32  Reserved1:1;
     UINT32  PLN:1;
     UINT32  ECMD:1;
     UINT32  PTM:1;
     UINT32  HWP:1;
     UINT32  HWP_Notification:1;
     UINT32  HWP_Activity_Window:1;
     UINT32  HWP_Energy_Performance_Preference:1;
     UINT32  HWP_Package_Level_Request:1;
     UINT32  Reserved2:1;
     UINT32  HDC:1;
     UINT32  TurboBoostMaxTechnology30:1;
     UINT32  HWPCapabilities:1;
     UINT32  HWPPECIOverride:1;
     UINT32  FlexibleHWP:1;
     UINT32  FastAccessMode:1;
     UINT32  Reserved4:1;
     UINT32  IgnoringIdleLogicalProcessorHWPRequest:1;
     UINT32  Reserved5:11;
   } Bits;
   UINT32  Uint32;
 } CPUID_THERMAL_POWER_MANAGEMENT_EAX;
  
 typedef union {
   struct {
     UINT32  InterruptThresholds:4;
     UINT32  Reserved:28;
   } Bits;
   UINT32  Uint32;
 } CPUID_THERMAL_POWER_MANAGEMENT_EBX;
  
 typedef union {
   struct {
     UINT32  HardwareCoordinationFeedback:1;
     UINT32  Reserved1:2;
     UINT32  PerformanceEnergyBias:1;
     UINT32  Reserved2:28;
   } Bits;
   UINT32  Uint32;
 } CPUID_THERMAL_POWER_MANAGEMENT_ECX;
  
  
 #define CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS                0x07
  
 #define CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_SUB_LEAF_INFO  0x00
  
 typedef union {
   struct {
     UINT32  FSGSBASE:1;
     UINT32  IA32_TSC_ADJUST:1;
     UINT32  SGX:1;
     UINT32  BMI1:1;
     UINT32  HLE:1;
     UINT32  AVX2:1;
     UINT32  FDP_EXCPTN_ONLY:1;
     UINT32  SMEP:1;
     UINT32  BMI2:1;
     UINT32  EnhancedRepMovsbStosb:1;
     UINT32  INVPCID:1;
     UINT32  RTM:1;
     UINT32  RDT_M:1;
     UINT32  DeprecateFpuCsDs:1;
     UINT32  MPX:1;
     UINT32  RDT_A:1;
     UINT32  AVX512F:1;
     UINT32  AVX512DQ:1;
     UINT32  RDSEED:1;
     UINT32  ADX:1;
     UINT32  SMAP:1;
     UINT32  AVX512_IFMA:1;
     UINT32  Reserved6:1;
     UINT32  CLFLUSHOPT:1;
     UINT32  CLWB:1;
     UINT32  IntelProcessorTrace:1;
     UINT32  AVX512PF:1;
     UINT32  AVX512ER:1;
     UINT32  AVX512CD:1;
     UINT32  SHA:1;
     UINT32  AVX512BW:1;
     UINT32  AVX512VL:1;
   } Bits;
   UINT32  Uint32;
 } CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_EBX;
  
 typedef union {
   struct {
     UINT32  PREFETCHWT1:1;
     UINT32  AVX512_VBMI:1;
     UINT32  UMIP:1;
     UINT32  PKU:1;
     UINT32  OSPKE:1;
     UINT32  Reserved5:9;
     UINT32  AVX512_VPOPCNTDQ:1;
     UINT32  Reserved7:1;
     UINT32  FiveLevelPage:1;
     UINT32  MAWAU:5;
     UINT32  RDPID:1;
     UINT32  Reserved3:7;
     UINT32  SGX_LC:1;
     UINT32  Reserved4:1;
   } Bits;
   UINT32  Uint32;
 } CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_ECX;
  
 typedef union {
   struct {
     UINT32  Reserved1:2;
     UINT32  AVX512_4VNNIW:1;
     UINT32  AVX512_4FMAPS:1;
     UINT32  Reserved4:11;
     UINT32  Hybrid:1;
     UINT32  Reserved5:10;
     UINT32  EnumeratesSupportForIBRSAndIBPB:1;
     UINT32  EnumeratesSupportForSTIBP:1;
     UINT32  EnumeratesSupportForL1D_FLUSH:1;
     UINT32  EnumeratesSupportForCapability:1;
     UINT32  EnumeratesSupportForCoreCapabilitiesMsr:1;
     UINT32  EnumeratesSupportForSSBD:1;
   } Bits;
   UINT32  Uint32;
 } CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS_EDX;
  
 #define CPUID_DIRECT_CACHE_ACCESS_INFO              0x09
  
  
 #define CPUID_ARCHITECTURAL_PERFORMANCE_MONITORING  0x0A
  
 typedef union {
   struct {
     UINT32  ArchPerfMonVerID:8;
     UINT32  PerformanceMonitorCounters:8;
     UINT32  PerformanceMonitorCounterWidth:8;
     UINT32  EbxBitVectorLength:8;
   } Bits;
   UINT32  Uint32;
 } CPUID_ARCHITECTURAL_PERFORMANCE_MONITORING_EAX;
  
 typedef union {
   struct {
     UINT32  UnhaltedCoreCycles:1;
     UINT32  InstructionsRetired:1;
     UINT32  UnhaltedReferenceCycles:1;
     UINT32  LastLevelCacheReferences:1;
     UINT32  LastLevelCacheMisses:1;
     UINT32  BranchInstructionsRetired:1;
     UINT32  AllBranchMispredictRetired:1;
     UINT32  Reserved:25;
   } Bits;
   UINT32  Uint32;
 } CPUID_ARCHITECTURAL_PERFORMANCE_MONITORING_EBX;
  
 typedef union {
   struct {
     UINT32  FixedFunctionPerformanceCounters:5;
     UINT32  FixedFunctionPerformanceCounterWidth:8;
     UINT32  Reserved1:2;
     UINT32  AnyThreadDeprecation:1;
     UINT32  Reserved2:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_ARCHITECTURAL_PERFORMANCE_MONITORING_EDX;
  
  
 #define CPUID_EXTENDED_TOPOLOGY                             0x0B
  
 typedef union {
   struct {
     UINT32  ApicIdShift:5;
     UINT32  Reserved:27;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_TOPOLOGY_EAX;
  
 typedef union {
   struct {
     UINT32  LogicalProcessors:16;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_TOPOLOGY_EBX;
  
 typedef union {
   struct {
     UINT32  LevelNumber:8;
     UINT32  LevelType:8;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_TOPOLOGY_ECX;
  
 #define   CPUID_EXTENDED_TOPOLOGY_LEVEL_TYPE_INVALID        0x00
 #define   CPUID_EXTENDED_TOPOLOGY_LEVEL_TYPE_SMT            0x01
 #define   CPUID_EXTENDED_TOPOLOGY_LEVEL_TYPE_CORE           0x02
  
  
 #define CPUID_EXTENDED_STATE                                0x0D
  
 #define CPUID_EXTENDED_STATE_MAIN_LEAF                      0x00
  
 typedef union {
   struct {
     UINT32  x87:1;
     UINT32  SSE:1;
     UINT32  AVX:1;
     UINT32  MPX:2;
     UINT32  AVX_512:3;
     UINT32  IA32_XSS:1;
     UINT32  PKRU:1;
     UINT32  Reserved1:3;
     UINT32  IA32_XSS_2:1;
     UINT32  Reserved2:18;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_STATE_MAIN_LEAF_EAX;
  
 #define CPUID_EXTENDED_STATE_SUB_LEAF                       0x01
  
 typedef union {
   struct {
     UINT32  XSAVEOPT:1;
     UINT32  XSAVEC:1;
     UINT32  XGETBV:1;
     UINT32  XSAVES:1;
     UINT32  Reserved:28;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_STATE_SUB_LEAF_EAX;
  
 typedef union {
   struct {
     UINT32  XCR0:1;
     UINT32  PT:1;
     UINT32  XCR0_1:1;
     UINT32  Reserved1:3;
     UINT32  HWPState:1;
     UINT32  Reserved8:18;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_STATE_SUB_LEAF_ECX;
  
 #define CPUID_EXTENDED_STATE_SIZE_OFFSET                    0x02
  
 typedef union {
   struct {
     UINT32  XSS:1;
     UINT32  Compacted:1;
     UINT32  Reserved:30;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_STATE_SIZE_OFFSET_ECX;
  
  
 #define CPUID_INTEL_RDT_MONITORING                          0x0F
  
 #define CPUID_INTEL_RDT_MONITORING_ENUMERATION_SUB_LEAF     0x00
  
 typedef union {
   struct {
     UINT32  Reserved1:1;
     UINT32  L3CacheRDT_M:1;
     UINT32  Reserved2:30;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_MONITORING_ENUMERATION_SUB_LEAF_EDX;
  
 #define CPUID_INTEL_RDT_MONITORING_L3_CACHE_SUB_LEAF        0x01
  
 typedef union {
   struct {
     UINT32  L3CacheOccupancyMonitoring:1;
     UINT32  L3CacheTotalBandwidthMonitoring:1;
     UINT32  L3CacheLocalBandwidthMonitoring:1;
     UINT32  Reserved:29;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_MONITORING_L3_CACHE_SUB_LEAF_EDX;
  
  
 #define CPUID_INTEL_RDT_ALLOCATION                          0x10
  
 #define CPUID_INTEL_RDT_ALLOCATION_ENUMERATION_SUB_LEAF     0x00
  
 typedef union {
   struct {
     UINT32  Reserved1:1;
     UINT32  L3CacheAllocation:1;
     UINT32  L2CacheAllocation:1;
     UINT32  MemoryBandwidth:1;
     UINT32  Reserved3:28;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_ALLOCATION_ENUMERATION_SUB_LEAF_EBX;
  
  
 #define CPUID_INTEL_RDT_ALLOCATION_L3_CACHE_SUB_LEAF        0x01
  
 typedef union {
   struct {
     UINT32  CapacityLength:5;
     UINT32  Reserved:27;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_ALLOCATION_L3_CACHE_SUB_LEAF_EAX;
  
 typedef union {
   struct {
     UINT32  Reserved3:2;
     UINT32  CodeDataPrioritization:1;
     UINT32  Reserved2:29;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_ALLOCATION_L3_CACHE_SUB_LEAF_ECX;
  
 typedef union {
   struct {
     UINT32  HighestCosNumber:16;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_ALLOCATION_L3_CACHE_SUB_LEAF_EDX;
  
 #define CPUID_INTEL_RDT_ALLOCATION_L2_CACHE_SUB_LEAF        0x02
  
 typedef union {
   struct {
     UINT32  CapacityLength:5;
     UINT32  Reserved:27;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_ALLOCATION_L2_CACHE_SUB_LEAF_EAX;
  
 typedef union {
   struct {
     UINT32  HighestCosNumber:16;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_ALLOCATION_L2_CACHE_SUB_LEAF_EDX;
  
 #define CPUID_INTEL_RDT_ALLOCATION_MEMORY_BANDWIDTH_SUB_LEAF        0x03
  
 typedef union {
   struct {
     UINT32  MaximumMBAThrottling:12;
     UINT32  Reserved:20;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_ALLOCATION_MEMORY_BANDWIDTH_SUB_LEAF_EAX;
  
 typedef union {
   struct {
     UINT32  Reserved1:2;
     UINT32  Liner:1;
     UINT32  Reserved2:29;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_ALLOCATION_MEMORY_BANDWIDTH_SUB_LEAF_ECX;
  
 typedef union {
   struct {
     UINT32  HighestCosNumber:16;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_RDT_ALLOCATION_MEMORY_BANDWIDTH_SUB_LEAF_EDX;
  
 #define CPUID_INTEL_SGX                                  0x12
  
 #define CPUID_INTEL_SGX_CAPABILITIES_0_SUB_LEAF          0x00
  
 typedef union {
   struct {
     UINT32  SGX1:1;
     UINT32  SGX2:1;
     UINT32  Reserved1:3;
     UINT32  ENCLV:1;
     UINT32  ENCLS:1;
     UINT32  Reserved2:25;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_SGX_CAPABILITIES_0_SUB_LEAF_EAX;
  
 typedef union {
   struct {
     UINT32  MaxEnclaveSize_Not64:8;
     UINT32  MaxEnclaveSize_64:8;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_SGX_CAPABILITIES_0_SUB_LEAF_EDX;
  
  
 #define CPUID_INTEL_SGX_CAPABILITIES_1_SUB_LEAF          0x01
  
  
 #define CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF  0x02
  
 typedef union {
   struct {
     UINT32  SubLeafType:4;
     UINT32  Reserved:8;
     UINT32  LowAddressOfEpcSection:20;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_EAX;
  
 typedef union {
   struct {
     UINT32  HighAddressOfEpcSection:20;
     UINT32  Reserved:12;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_EBX;
  
 typedef union {
   struct {
     UINT32  EpcSection:4;
     UINT32  Reserved:8;
     UINT32  LowSizeOfEpcSection:20;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_ECX;
  
 typedef union {
   struct {
     UINT32  HighSizeOfEpcSection:20;
     UINT32  Reserved:12;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_SGX_CAPABILITIES_RESOURCES_SUB_LEAF_EDX;
  
  
 #define CPUID_INTEL_PROCESSOR_TRACE                         0x14
  
 #define CPUID_INTEL_PROCESSOR_TRACE_MAIN_LEAF               0x00
  
 typedef union {
   struct {
     UINT32  Cr3Filter:1;
     UINT32  ConfigurablePsb:1;
     UINT32  IpTraceStopFiltering:1;
     UINT32  Mtc:1;
     UINT32  PTWrite:1;
     UINT32  PowerEventTrace:1;
     UINT32  Reserved:26;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_PROCESSOR_TRACE_MAIN_LEAF_EBX;
  
 typedef union {
   struct {
     UINT32  RTIT:1;
     UINT32  ToPA:1;
     UINT32  SingleRangeOutput:1;
     UINT32  TraceTransportSubsystem:1;
     UINT32  Reserved:27;
     UINT32  LIP:1;
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_PROCESSOR_TRACE_MAIN_LEAF_ECX;
  
  
 #define CPUID_INTEL_PROCESSOR_TRACE_SUB_LEAF                0x01
  
 typedef union {
   struct {
     UINT32  ConfigurableAddressRanges:3;
     UINT32  Reserved:13;
     UINT32  MtcPeriodEncodings:16;
  
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_PROCESSOR_TRACE_SUB_LEAF_EAX;
  
 typedef union {
   struct {
     UINT32  CycleThresholdEncodings:16;
     UINT32  PsbFrequencyEncodings:16;
  
   } Bits;
   UINT32  Uint32;
 } CPUID_INTEL_PROCESSOR_TRACE_SUB_LEAF_EBX;
  
  
 #define CPUID_TIME_STAMP_COUNTER                            0x15
  
  
 #define CPUID_PROCESSOR_FREQUENCY                           0x16
  
 typedef union {
   struct {
     UINT32  ProcessorBaseFrequency:16;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_PROCESSOR_FREQUENCY_EAX;
  
 typedef union {
   struct {
     UINT32  MaximumFrequency:16;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_PROCESSOR_FREQUENCY_EBX;
  
 typedef union {
   struct {
     UINT32  BusFrequency:16;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_PROCESSOR_FREQUENCY_ECX;
  
  
 #define CPUID_SOC_VENDOR                                    0x17
  
 #define CPUID_SOC_VENDOR_MAIN_LEAF                          0x00
  
 typedef union {
   struct {
     UINT32  SocVendorId:16;
     UINT32  IsVendorScheme:1;
     UINT32  Reserved:15;
   } Bits;
   UINT32  Uint32;
 } CPUID_SOC_VENDOR_MAIN_LEAF_EBX;
  
 #define CPUID_SOC_VENDOR_BRAND_STRING1                      0x01
  
 typedef union {
   CHAR8   BrandString[4];
   UINT32  Uint32;
 } CPUID_SOC_VENDOR_BRAND_STRING_DATA;
  
 #define CPUID_SOC_VENDOR_BRAND_STRING2                      0x02
  
 #define CPUID_SOC_VENDOR_BRAND_STRING3                      0x03
  
 #define CPUID_DETERMINISTIC_ADDRESS_TRANSLATION_PARAMETERS             0x18
  
 #define CPUID_DETERMINISTIC_ADDRESS_TRANSLATION_PARAMETERS_MAIN_LEAF   0x00
  
 typedef union {
   struct {
     UINT32  Page4K:1;
     UINT32  Page2M:1;
     UINT32  Page4M:1;
     UINT32  Page1G:1;
     UINT32  Reserved1:4;
     UINT32  Partitioning:3;
     UINT32  Reserved2:5;
     UINT32  Way:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_DETERMINISTIC_ADDRESS_TRANSLATION_PARAMETERS_EBX;
  
 typedef union {
   struct {
     UINT32  TranslationCacheType:5;
     UINT32  TranslationCacheLevel:3;
     UINT32  FullyAssociative:1;
     UINT32  Reserved1:5;
     UINT32  MaximumNum:12;
     UINT32  Reserved2:6;
   } Bits;
   UINT32  Uint32;
 } CPUID_DETERMINISTIC_ADDRESS_TRANSLATION_PARAMETERS_EDX;
  
 #define   CPUID_DETERMINISTIC_ADDRESS_TRANSLATION_PARAMETERS_TRANSLATION_CACHE_TYPE_INVALID          0x00
 #define   CPUID_DETERMINISTIC_ADDRESS_TRANSLATION_PARAMETERS_TRANSLATION_CACHE_TYPE_DATA_TLB         0x01
 #define   CPUID_DETERMINISTIC_ADDRESS_TRANSLATION_PARAMETERS_TRANSLATION_CACHE_TYPE_INSTRUCTION_TLB  0x02
 #define   CPUID_DETERMINISTIC_ADDRESS_TRANSLATION_PARAMETERS_TRANSLATION_CACHE_TYPE_UNIFIED_TLB      0x03
  
  
 #define CPUID_HYBRID_INFORMATION                                       0x1A
  
 #define CPUID_HYBRID_INFORMATION_MAIN_LEAF                              0x00
  
 typedef union {
   struct {
     UINT32  NativeModelId:24;
     UINT32  CoreType:8;
   } Bits;
   UINT32  Uint32;
 } CPUID_NATIVE_MODEL_ID_AND_CORE_TYPE_EAX;
  
 #define   CPUID_CORE_TYPE_INTEL_ATOM                                    0x20
 #define   CPUID_CORE_TYPE_INTEL_CORE                                    0x40
  
  
 #define CPUID_V2_EXTENDED_TOPOLOGY                                     0x1F
  
 #define   CPUID_V2_EXTENDED_TOPOLOGY_LEVEL_TYPE_MODULE                  0x03
 #define   CPUID_V2_EXTENDED_TOPOLOGY_LEVEL_TYPE_TILE                    0x04
 #define   CPUID_V2_EXTENDED_TOPOLOGY_LEVEL_TYPE_DIE                     0x05
  
 #define CPUID_EXTENDED_FUNCTION                 0x80000000
  
  
 #define CPUID_EXTENDED_CPU_SIG                  0x80000001
  
 typedef union {
   struct {
     UINT32  LAHF_SAHF:1;
     UINT32  Reserved1:4;
     UINT32  LZCNT:1;
     UINT32  Reserved2:2;
     UINT32  PREFETCHW:1;
     UINT32  Reserved3:23;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_CPU_SIG_ECX;
  
 typedef union {
   struct {
     UINT32  Reserved1:11;
     UINT32  SYSCALL_SYSRET:1;
     UINT32  Reserved2:8;
     UINT32  NX:1;
     UINT32  Reserved3:5;
     UINT32  Page1GB:1;
     UINT32  RDTSCP:1;
     UINT32  Reserved4:1;
     UINT32  LM:1;
     UINT32  Reserved5:2;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_CPU_SIG_EDX;
  
  
 #define CPUID_BRAND_STRING1                     0x80000002
  
 typedef union {
   CHAR8   BrandString[4];
   UINT32  Uint32;
 } CPUID_BRAND_STRING_DATA;
  
 #define CPUID_BRAND_STRING2                     0x80000003
  
 #define CPUID_BRAND_STRING3                     0x80000004
  
  
 #define CPUID_EXTENDED_CACHE_INFO               0x80000006
  
 typedef union {
   struct {
     UINT32  CacheLineSize:8;
     UINT32  Reserved:4;
     UINT32  L2Associativity:4;
     UINT32  CacheSize:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_CACHE_INFO_ECX;
  
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_DISABLED       0x00
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_DIRECT_MAPPED  0x01
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_2_WAY          0x02
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_4_WAY          0x04
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_8_WAY          0x06
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_16_WAY         0x08
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_32_WAY         0x0A
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_48_WAY         0x0B
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_64_WAY         0x0C
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_96_WAY         0x0D
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_128_WAY        0x0E
 #define CPUID_EXTENDED_CACHE_INFO_ECX_L2_ASSOCIATIVITY_FULL           0x0F
  
 #define CPUID_EXTENDED_TIME_STAMP_COUNTER       0x80000007
  
 typedef union {
   struct {
     UINT32  Reserved1:8;
     UINT32  InvariantTsc:1;
     UINT32  Reserved2:23;
   } Bits;
   UINT32  Uint32;
 } CPUID_EXTENDED_TIME_STAMP_COUNTER_EDX;
  
  
 #define CPUID_VIR_PHY_ADDRESS_SIZE              0x80000008
  
 typedef union {
   struct {
     UINT32  PhysicalAddressBits:8;
     UINT32  LinearAddressBits:8;
     UINT32  Reserved:16;
   } Bits;
   UINT32  Uint32;
 } CPUID_VIR_PHY_ADDRESS_SIZE_EAX;
  
 #endif

