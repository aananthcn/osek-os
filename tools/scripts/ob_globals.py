
# OSEK Builder Global Variables (OB Globals)
# ------------------------------------------
# list of column titles in TASK tab of OSEX-Builder.xlsx
TaskParams = ["Task Name", "PRIORITY", "SCHEDULE", "ACTIVATION", "AUTOSTART",
    "RESOURCE", "EVENT", "MESSAGE"]
TNMI = 0
PRII = 1
SCHI = 2
ACTI = 3
ATSI = 4
RESI = 5
EVTI = 6
MSGI = 7


# list of column titles in TASK tab of OSEX-Builder.xlsx
CntrParams = ["Counter Name", "MINCYCLE", "MAXALLOWEDVALUE", "TICKSPERBASE",
     "TICKDURATION"]

# Column titles for Alarms
AlarmParams = ["Alarm Name", "COUNTER", "Action-Type", "arg1", "arg2", "IsAutostart",
	"ALARMTIME", "CYCLETIME", "APPMODE[]" ]

# Column titles for ISRs
ISR_Params = ["ISR Name", "CATEGORY", "RESOURCE", "MESSAGE"]

if __name__ == '__main__':
	print("OSEK Builder Globals")
