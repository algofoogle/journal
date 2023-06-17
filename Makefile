PREVIOUS := $(shell ls -1 0[0-9][0-9][0-9]-*.md | sort | tail -1)
LAST := $(shell echo "$(PREVIOUS)" | cut -d- -f1)
NEXT := $(shell printf '%04d' `expr $(LAST) + 1`)
STAMP := $(shell date +%F)
TODAY := $(shell date +'%-d %b %Y')
NEXTFILE := $(NEXT)-$(STAMP).md

new:
	@echo "# $(TODAY)" >> $(NEXTFILE)
	@echo >> $(NEXTFILE)
	@echo "| Previous journal: | Next journal: |" >> $(NEXTFILE)
	@echo "|-|-|" >> $(NEXTFILE)
	@echo "| [$(PREVIOUS)](./$(PREVIOUS)) | *Next journal TBA* |" | sed -re "s/\[([0-9]{4})-/[**\1**-/" >> $(NEXTFILE)
	@echo Do not forget to update $(PREVIOUS) previous/next chain
	@echo '*   ['$(NEXTFILE)'](./'$(NEXTFILE)'): ' >> README.md
	@echo Created: $(NEXTFILE)

.PHONY: new
