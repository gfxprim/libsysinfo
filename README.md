# System information and statistics extraction library for Linux

Supports:

- battery information
- cpu information
- cpu statistics
- memory statistics

Example output:

```
$ bat_info_test
Power source:   Mains
-----------------------

Online:         Yes


Power source:   Battery
-----------------------

Cycle count:    266
Voltage:        12.252000 V
Technology:     Li-poly

Status:         Not Charging
State now:      39700.0 mWh
State full:     39860.0 mWh
State design:   45280.0 mWh
```

```
$ cpu_info_test
Vendor          : Intel
Architecture    : Sky Lake
Model name      : i7-8550U
Processors      : 4
Cores           : 8

CPU temp driver : coretemp

CPU Load :  19% | CPU Temp :  44C
```

```
$ mem_info_test
MemTotal        : 24510348 kB
MemFree         : 2042536 kB
MemCached       : 8097512 kB
SwapTotal       : 4194300 kB
SwapFree        : 3730400 kB
```
