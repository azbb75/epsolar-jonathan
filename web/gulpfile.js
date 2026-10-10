'use strict';

var del = require('del');
var gulp = require('gulp');
var htmlmin = require('gulp-htmlmin');
var inlinesource = require('gulp-inline-source');

// Task to inline HTML file
gulp.task('inline', function() {
    return gulp.src(['./index.html'])
      .pipe(htmlmin({
        collapseWhitespace: true,
        removeComments: true
      }))
      .pipe(inlinesource())
      .pipe(gulp.dest('./dist'));
  });

// Task to clean the dist folder
gulp.task('clean', () => del(['./dist']));

// Default task
gulp.task('default', gulp.series('clean', 'inline', function (done) {
    done();
}));