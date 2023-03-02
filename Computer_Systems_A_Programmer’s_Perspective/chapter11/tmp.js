function calculateDaysBetweenDates(begin, end) {
  const beginDate = new Date(begin);
  const endDate = new Date(end);
  const difference = endDate.getTime() - beginDate.getTime();
  const days = difference / (1000 * 3600 * 24);
  return days;
}

// find all images without alternate text
// and give them a red border
const images = document.querySelectorAll('img');
// Return the current time in milliseconds
const now = Date.now();
