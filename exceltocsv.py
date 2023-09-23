import os
import pandas as pd

path = "C:\\Users\\SUGAM SHAW\\OneDrive\\Desktop\\c programs\\CASE STUDY DS"

files = os.listdir(path)
for eachfile in files:
    if eachfile.endswith(".xlsx"):
        cleanfilename=eachfile.replace(".xlsx","")
        xlfile = pd.ExcelFile(eachfile)
        sheets = xlfile.sheet_names
        for eachsheet in sheets:
            sheetdata = xlfile.parse(eachsheet)
            csvname = cleanfilename + "-" + eachsheet+".csv"
            sheetdata.to_csv(csvname,index=False)

print("done")
