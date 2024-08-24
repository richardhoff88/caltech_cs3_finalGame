#ifndef __ASSET_H__
#define __ASSET_H__

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <color.h>
//#include <sdl_wrapper.h>
#include <stddef.h>
#include "body.h"
#include "state.h"

typedef enum { ASSET_IMAGE, ASSET_FONT, ASSET_BUTTON, ASSET_BODY} asset_type_t;

typedef struct asset asset_t;

/**
 * A button handler.
 *
 * @param state the state of the game.
 */
typedef void (*button_handler_t)(void *state);

/**
 * Gets the `asset_type_t` of the asset.
 *
 * @return the type of the asset.
 */
asset_type_t asset_get_type(asset_t *asset);

/**
 * Allocates memory for an asset with a body
 *
 * @param body the body to render
 * @return a pointer to the newly allocated body asset
 */
asset_t *asset_make_body(body_t *body);

/**
 * Returns the body of the asset if there is one in the asset.
 *
 * @param asset a pointer to the asset
 * @return a pointer to the body in the asset if it exists
 */
body_t *asset_get_body(asset_t *asset);

/**
 * Allocates memory for an image asset with the given parameters.
 *
 * @param filepath the filepath to the image file
 * @param bounding_box the bounding box containing the location and dimensions
 * of the text when it is rendered
 * @return a pointer to the newly allocated image asset
 */
asset_t *asset_make_image(const char *filepath, SDL_Rect bounding_box);

/**
 * Allocates memory for an image asset with an attached body. When the asset
 * is rendered, the image will be rendered on top of the body.
 *
 * @param filepath the filepath to the image file
 * @param body the body to render the image on top of
 * @return a pointer to the newly allocated image asset
 */
asset_t *asset_make_image_with_body(const char *filepath, body_t *body);

/**
 * Allocates memory for a text asset with the given parameters.
 *
 * @param filepath the filepath to the .ttf file
 * @param bounding_box the bounding box containing the location and dimensions
 * of the text when it is rendered
 * @param text the text to render
 * @param color the color of the text
 * @return a pointer to the newly allocated text asset
 */
asset_t *asset_make_text(const char *filepath, SDL_Rect bounding_box,
                         const char *text, rgb_color_t color);

/**
 * A button handler.
 *
 * @param state the state of the game
 */
typedef void (*button_handler_t)(void *state);

/**
 * Allocates memory for a button asset with the given parameters.
 * Note that `image_asset` and `text_asset` should be owned by the caller. Thus,
 * `asset_destroy` will only free the memory allocated for the button.
 *
 * Asserts that `image_asset` is NULL or has type `ASSET_IMAGE`.
 * Asserts that `text_asset` is NULL or has type `ASSET_FONT`.
 *
 * @param bounding_box the bounding box containing the area on the screen that
 * should activate the button handler.
 * @param image_asset the image that the button renders. Can be NULL.
 * @param text_asset the text that the button renders. Can be NULL.
 * @param handler the button handler that runs when the button is clicked.
 */
asset_t *asset_make_button(SDL_Rect bounding_box, asset_t *image_asset,
                           asset_t *text_asset, button_handler_t handler);

/**
 * Runs the button handler for `button` if
 *
 * 1. `x` and `y` are contained in the button's bounding box.
 * 2. AND `button` is currently rendered onto the screen.
 *
 * @param button the pointer to the button asset
 * @param state the game state
 * @param x the x position of the mouse click
 * @param y the y position of the mouse click
 */
void asset_on_button_click(asset_t *button, state_t *state, double x, double y);

/**
 * Sets the image texture for an asset if it is a button or an image with a
 * new filepath.
 * 
 * @param asset pointer to the asset
 * @param filepath path to new image file
*/
void asset_set_image(asset_t *asset, const char *filepath);

/**
 * Renders the asset to the screen.
 * @param asset the asset to render
 */
void asset_render(asset_t *asset);

/**
 * Frees the memory allocated for the asset.
 * @param asset the asset to free
 */
void asset_destroy(asset_t *asset);

#endif // #ifndef __ASSET_H__
