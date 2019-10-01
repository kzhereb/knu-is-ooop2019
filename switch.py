import collections
import glob
import os 
import sys

project_dir = os.path.dirname(os.path.realpath(__file__))

ReplaceRule = collections.namedtuple("ReplaceRule", ["mask","on","off"])


def replace_single(filename,src, dest):
    print("file {0}: {1}=>{2}".format(filename,repr(src), repr(dest)) )
    with open(filename,'r+', encoding="utf-8") as file:
        text = file.read()
        
        new_text = text.replace(src,dest)
        
        if new_text == text:
            print("    no changes")
        else:
            file.seek(0)
            file.write(new_text)
            file.truncate() 

def replace_all(rule, is_on):
    for filename in glob.iglob(rule.mask):
        full_name = os.path.join(project_dir,filename)
        if is_on:
            replace_single(full_name,rule.off,rule.on)
        else:
            replace_single(full_name,rule.on,rule.off)

def init_rules():
    rules = {}
    rules["list"] = [ReplaceRule("oop-intro-list/doubly_linked_list.cpp",
                                 "int main()",
                                 "int main_list()")]
    rules["catch"] = [ReplaceRule("unit-testing/catch_main.cpp",
                                  "\n#define CATCH_CONFIG_MAIN",
                                  "\n//#define CATCH_CONFIG_MAIN"),
                      ReplaceRule("unit-testing/*.cpp",
                                  "\n//#define CATCH_CONFIG_DISABLE",
                                  "\n#define CATCH_CONFIG_DISABLE")] 
    
    return rules
   
def main(option):
    rules = init_rules()
    
    for name,rules in rules.items():
            for rule in rules:
                replace_all(rule, option==name or option=="on")
    
#     if option == "on":
#         for name,rules in rules.items():
#             for rule in rules:
#                 replace_all(rule, True)
#     else:
#         for name,rule in rules.items():
#                         for rule in rules:
#                 replace_all(rule, True)
#             replace_all(rule, option==name)


if __name__ == "__main__":
   main(sys.argv[1])