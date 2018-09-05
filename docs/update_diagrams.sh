# find . -name "*.plantuml" >> var
# for i in var; 
# do 
# 	echo "hello $i"; 
# done

text_files="$(find . -name '*.plantuml')"
for i in $text_files; 
do 
	java -jar "../plantuml.jar" $i; 
done
