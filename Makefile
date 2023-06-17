PREVIOUS := $(shell ls -1 0[0-9][0-9][0-9]-*.md | sort | tail -1)
LAST := $(shell echo "$(PREVIOUS)" | cut -d- -f1)
NEXT := $(shell printf '%04d' `expr $(LAST) + 1`)
STAMP := $(shell date +%F)
TODAY := $(shell date +'%-d %b %Y')
NEXTFILE := $(NEXT)-$(STAMP).md
NEXTFILESEDLINK := $(shell echo '[**')$(NEXT)$(shell echo '**')-$(STAMP).md](.\/$(NEXTFILE))

new:
	@echo '*   ['$(NEXTFILE)'](./'$(NEXTFILE)'): ' >> README.md
	@echo "Updated README.md"
	@echo "# $(TODAY)" >> $(NEXTFILE)
	@echo >> $(NEXTFILE)
	@echo "| Previous journal: | Next journal: |" >> $(NEXTFILE)
	@echo "|-|-|" >> $(NEXTFILE)
	@echo "| [$(PREVIOUS)](./$(PREVIOUS)) | *Next journal TBA* |" | sed -re "s/\[([0-9]{4})-/[**\1**-/" >> $(NEXTFILE)
	@echo "Created: $(NEXTFILE)"
	@echo "Updating chain in $(PREVIOUS):"
	@sed -i -re "s/[*]Next journal TBA[*]/$(NEXTFILESEDLINK)/" $(PREVIOUS)
	@fgrep "$(NEXTFILE)" $(PREVIOUS)

.PHONY: new
