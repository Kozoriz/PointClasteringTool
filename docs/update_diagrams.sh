# find . -name "*.plantuml" >> var
# for i in var; 
# do 
# 	echo "hello $i"; 
# done

text_files="$(find . -name '*.plantuml')"
for i in $text_files; 
do 
	java -DPLANTUML_LIMIT_SIZE=65536 -jar "../plantuml.jar" $i; 
done
