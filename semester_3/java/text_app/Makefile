SRC_DIR = src
OUT_DIR = out
JAR     = textApp.jar
MAIN    = textApp

.PHONY: all build run clean distclean

all: build

build: clean
	mkdir -p $(OUT_DIR)
	javac -encoding UTF-8 -d $(OUT_DIR) $(SRC_DIR)/*.java
	jar cfe $(JAR) $(MAIN) -C $(OUT_DIR) .

run:
	java -ea -Dfile.encoding=UTF-8 -jar $(JAR)

clean:
	rm -rf $(OUT_DIR)

distclean: clean
