# Song Sorter
This program is designed to make it easy for people to sort & rank their favorite songs, artists, and albums. It will accomplish this by first getting a list of songs from the user and then presenting to the user a pair of songs and having them choose which one of the two they like more. The program will then continue to present pairs of songs to the user until each song is sorted.

## Planned features
* Efficient Sorting
  * The sorting method will try to reduce the number of comparisons as much as possible. It will attempt to do this by using a self-balancing binary tree to store the results of each comparison.
* Media Player Functionality
  * When the user is prompted to compare songs, they will have the option of listening to them so that they can make a more accurate decision about which one they prefer.
* Categorization of Results
  * The user will have the option of having the results grouped into categories such that they will be able to see how each group of songs compares to one another. There will also be a variety of different ways in which the groups can be sorted.
  * Planned Categories:
    * Album
    * Artist
    * Genre
    * Year
    * Decade
  * Planned Sorting Methods:
    * Average Rank
    * Median Rank
    * Highest/Lowest Rank of Individual Song
    * All of the above with the ability to only take into account the highest-ranked or lowest-ranked half of songs in the group.
* Ability to Export Results
  * The user will be able to export the results of the sorting to a csv file. This option will be available for both grouped and ungrouped results.
* Playlist Generation
  * The user will also be able to generate playlists using the results of the sorting.

## Plan for Implementation
### Phase 1: Basic Functionality
- [ ] GUI Layout
- [ ] Song Importing
- [ ] Media Player
- [ ] Song Sorting
- [ ] Output File Generation
- [ ] Installer Creation
### Phase 2: Additional Features
- [ ] Additional Categories and Sorting Methods
- [ ] Playlist Generation
- [ ] GUI visual improvements
