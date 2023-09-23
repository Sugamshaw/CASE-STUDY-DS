import pandas as pd
data=pd.read_csv('TOTAL_USER_CSV.csv')

selected_columns = data[["MINAKSHI KUMARI", "2201020094"]]


df = pd.DataFrame(data)

# Iterate through each row in the DataFrame
for index, row in df.iterrows():
    name = row["MINAKSHI KUMARI"]
    password = row["2201020094"]
    new_csv_path=name+str(password)+".csv"
    selected_columns.to_csv(new_csv_path, index=False)

# for i in selected_columns:
#     for j in i:
#         print(j)
# for i in range(90):
#     new_csv_path = "new_file.csv"
#     selected_columns.to_csv(new_csv_path, index=False)
