import fileinput
import re 

def write2file(text, filename2, mod):
    f=open(filename2,mod)
    f.write(text)
    f.close()

filename = 'a9a'
f = open(filename, 'r+')
str_ele=''
line_index=0;
pattern = re.compile(' +[0-9]+:{1}[0-9]+\.?[0-9]*')

for line in fileinput.input(filename):
    if len(line)<1:
        continue
    write2file(line[0:2]+"\n","label.txt", 'a+')#write to label file 
    x=line[2:]
    res = pattern.findall(x)
    for data in res:
        ele = data[1:].split(':')
        str_ele = str_ele + str(line_index)+' '+ele[0]+ ' '+ ele[1]+'\n';    
    line_index = line_index+1
    if line_index%1000==0:
        write2file(str_ele,"data.txt",'a+')
        str_ele=''


