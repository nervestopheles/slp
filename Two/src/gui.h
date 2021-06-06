void SetFont(struct nk_context *nk_ctx, const char *font_path, const unsigned char font_size);
void SetMenuColor(struct nk_context *nk_ctx);

void UpdateMenuPosition(struct nk_rect *menu, int x, int y, int w, int h);

void Intro  (SDL_Window *, struct nk_context *);
void Canvas (SDL_Window *, struct nk_context *);
void ViewMatrix (struct nk_context * nk_ctx, struct nk_rect * menu);
void DataEditor(struct nk_context * nk_ctx, struct nk_rect * region,
    float data[furnace_count][furnace_count]);
