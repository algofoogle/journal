LATEST := $(shell ls -1 ????-*.md | sort | tail -1 | cut -d- -f1)
NEXT := $(shell printf '%04d' `expr $(LATEST) + 1`)
STAMP := $(shell date +%F)
TODAY := $(shell date +'%-d %b %Y')
NEXTFILE := $(NEXT)-$(STAMP).md

new:
	@echo "# $(TODAY)" >> $(NEXTFILE)
	@echo '*   ['$(NEXTFILE)'](./'$(NEXTFILE)'): ' >> README.md
	@echo Created: $(NEXTFILE)

.PHONY: new
