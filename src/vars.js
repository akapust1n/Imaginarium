let vars = {};
window.location.search.substring(1).split('&').forEach(pair => {
    let pairSplit = pair.split('=');
    vars[pairSplit[0]] = pairSplit[1];
});

export default vars;